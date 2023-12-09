/**  @file srv.c
*    @brief implementation of methods for server part.
*    
*    
*    
*
*    @author Kekalo Kateryna
*/



#include "srv.h"




int server(){

    int len_cli_id = N_CLIENTS + 4;
    char clients_id[len_cli_id][BUFLEN]; // +3 (file descriptors for standart I/O) + 1 (file desctiptor for .tmp.txt)
// масив де і-ий елемент це ідентифікатор клієнта, який обслуговується на і-тому файловому дескрипторі

    for (int i = 0; i < len_cli_id; i++) strcpy(clients_id[i], "  ");

    int i, err, opt=1;
    int sock, new_sock;
    struct sockaddr_in addr;
    struct sockaddr_in client;
    char buf[BUFLEN];
    char inp[BUFLEN];
    socklen_t size;
    FILE * fout;
    fout = fopen(TEMPFILENAME, "w");					// відкриття файлу куди записуватимуться повідомлення користувачам яких немає в мережі

    //створення сокету
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if ( sock < 0 ) {
        perror("Server: cannot create socket");
        exit (EXIT_FAILURE);
    }
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // зв'язування сокету
    addr.sin_family = PF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);				// прив'язка до будь-якої локальної адреси
    err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if ( err<0 ) {
        perror("Server: cannot bind socket\n");
        exit(EXIT_FAILURE);
    }


    // чекаємо на приєднання
    err = listen(sock, 3);
    if ( err<0 ){
        perror ("Server: listen queue failure");
        exit(EXIT_FAILURE);
    }


    pollfd act_set[N_CLIENTS];
    act_set[0].fd = sock;						//додаємо перший сокет(слухаючий)
    act_set[0].events = POLLIN;						//встановлюємо яку подію ми будемо моніторити
    act_set[0].revents = 0;						//встановлюємо статус в початкове положення
    int num_set = 1;
    



    while(1) {
        int ret = poll(act_set, num_set, -1);				//запуск методу poll() для паралельного обслуговування багатьох клієнтів
        if ( ret<0 ){
            perror("Server: poll failure");
            exit(EXIT_FAILURE);
        }
        
        if ( ret>0 ){
            for (i=0; i<num_set; i++){					//обходимо підключених користувачів
                if (act_set[i].revents & POLLIN){			//перевіряємо який саме користувач надіслав повідомлення
                    printf("Get POLLIN at fd %d\n", act_set[i].fd);
                    act_set[i].revents = 0;				//встановлюємо статус в початкове положення для подальшого моніторингу
                    if ( i==0 ){					//0-ий файловий дескриптор -- той який під'єднує користувачів(якщо він спрацював -- нове приєднання)
                        size = sizeof(client);
                        new_sock = accept(act_set[i].fd, (struct sockaddr*)&client, &size);
                        printf("new client at port %u\n", ntohs(client.sin_port));
                        if ( num_set<N_CLIENTS){
                            act_set[num_set].fd = new_sock;		// додаємо клієнта в структуру pollfd
                            act_set[num_set].events = POLLIN;
                            act_set[num_set].revents = 0;
                            num_set++;

                            read(new_sock, buf, BUFLEN); 		//читаємо ідентифікатор клієнта 
                            strcpy(clients_id[new_sock], buf);

                            fclose(fout);
                            resend(new_sock, buf);
                            FILE * fout;
                            fout = fopen(TEMPFILENAME, "a");
                            
                        }
                        else{
                            printf("No more sockets for clients");
                            close(new_sock);
                        }
                    } else{						//якщо це не 0-ий сокет значить вже існуючий клієнт надсилає повідомлення
                        err = readFromClient(act_set[i].fd, buf);	//читаємо його

                        
                        printf("[%s] \n", buf);
                        if ( err<0 || strstr(buf, "stop")){		//якщо помилка читання то закриваємо файловий дескриптор для цього клієнта
                            printf("get stop\n");
                            close(act_set[i].fd);
                            if (i<num_set-1){
                                strcpy(clients_id[act_set[i].fd], "  ");   //чистимо місце в списку ідентифікаторів	
                                act_set[i] = act_set[num_set-1];
                                num_set --;
                                i--;
                            }
                        }
                        else {
                            if ( !find_client(buf, clients_id, len_cli_id) ) {   //якщо помилки немає, то шукаємо користувача,якому адрксоване првідомлення
                                fprintf(fout, "%s", buf);     //якщо не знайшли, то записуємо повідомлення в тимчасовий файл
                                fprintf(fout, "\n");
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}


void resend(int fd, char * cli_id){
    bool start; 
    FILE * inp;
    inp = fopen(TEMPFILENAME, "r");		// відкриваємо тимчасовий файл куди записувались повідомлення користувачам, яких не було в мережі
    
    if (inp!=NULL)start = true;
    else start = false;
    char msg[BUFLEN];
    while (start){
        int t = fscanf(inp, "%s", msg);		//читаю по рядку
        if (feof(inp)) break;
        char * token = strtok(msg, "|");	//розбиваю рядок на дві частини
        int f = 0;
        while ( token ){			
            if ( !f ){
                if ( !strcmp(token, cli_id) ){ 	//перевіряю чи дійсно цьому користувачу повідомлення
                token = strtok(NULL, "|");
                f = 1;
                } else break;
            }
            else {
                writeToClient(fd, token);
                break;
            }
        } 
    }
    fclose(inp);
}


int find_client(char * buf, char clients[][BUFLEN], int n_clients){
    char s[BUFLEN];
    strcpy(s, buf);
    char * token = strtok(s, "|");
    int f = 0;
    int cli_fd;
    while (token)
    {   
        if (!f){
            for(int i = 2; i < n_clients; i++){
                if ( !strcmp(token, clients[i]) ){
                    f = 1;
                    cli_fd = i;
                    break;
                }
            }
            if (!f) {
                return 0;
            }
            else { token = strtok(NULL, "|"); }
        }
        else {
            writeToClient(cli_fd, token);
            return 1;
        }
    }
}



int readFromClient (int fd, char *buf) {
 
    int nbytes;

    nbytes = read(fd, buf, BUFLEN);
    if ( nbytes < 0 ) {
        perror("Read error\n");
        return -1;
    }else if (nbytes == 0) {
        printf("Client no message\n");   
        return -1;
    }
    else {
        printf("Server got a message %s\n", buf);
        return 0;
    }
}


void writeToClient (int fd, char *buf)
{
    int nbytes;
    // unsigned char *s;

    // for (s=(unsigned char*)buf; *s; s++) *s = toupper(*s);
    nbytes = write(fd, buf, strlen(buf) + 1);
    printf("Write back: %s\nnbytes=%d\n", buf, nbytes);

    if ( nbytes < 0 ){
        perror("Server: write failure");
    }
}
