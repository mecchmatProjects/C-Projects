/**  @file cli.c
*    @brief implementation of methods for client part.
*    
*    
*    
*
*    @author Kekalo Kateryna
*/




#include "cli.h"

int sock; 
char * cli_id;			
char client_name[20];

volatile sig_atomic_t flag = 0;

void catch_ctrl_c_and_exit(int sig){
    flag = 1;
}


void * writeToServer(void *arg ){

    InputOutput * args = arg; 

    int nbytes;
    char buf[BUFLEN];

    while(1){
        fprintf(args->outstream, "Enter message starting with 'user_name | '");
        fscanf(args->instream, "%s", buf );
        buf[strlen(buf)-1] = 0;

        nbytes = write(sock, buf, strlen(buf)+1);
        if (nbytes < 0)  break;
        if (strstr(buf, "stop")) break;
    }
    catch_ctrl_c_and_exit(2);

}


void * readFromServer (void *arg) {

    InputOutput * args = arg; 
    int nbytes;
    char buf[BUFLEN];

    while(1){
        nbytes = read(sock, buf, BUFLEN);
        if ( nbytes < 0 ) {
            perror("Read error\n");
            break;
        }else if (nbytes == 0) {
            fprintf(args->outstream, "\nServer no message\n");   
            break;
        }
        else {
            fprintf(args->outstream, "\n[server] %s\n", buf);
        }
    }
}

void cli(FILE * instream, FILE * outstream){
    signal(SIGINT, catch_ctrl_c_and_exit);

    fprintf(stdout, "Enter your nickname: ");
    fscanf(instream, "%s", client_name);


    int err;
    struct sockaddr_in server_addr;
    struct hostent *hostinfo;
    hostinfo = gethostbyname(SERVER_NAME);
    if ( NULL == hostinfo ) {
        fprintf (stderr, "Unknown host %s. \n", SERVER_NAME);
        exit (EXIT_FAILURE);
    }

    
    // Створення сокета
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock < 0 ) {
        perror ("Client: socket was not created ");
        exit (EXIT_FAILURE);
    }


    // Під'єднання до сервера 
    err = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if ( err < 0 ) {
        perror("Client: connect failure");
        exit(EXIT_FAILURE);
    }
    fprintf(outstream, "Connection is ready\n");
    
    // Передача ідентифікатора клієнта
    write(sock, client_name, strlen(client_name)+1);
	
    //заповнення структури для різних можливостей вводу виводу
    InputOutput *args = malloc(sizeof *args);
    args->instream = instream; 
    args->outstream = outstream; 
	
    //створення нових потоків 
    pthread_t write_to_server;

    if (pthread_create(&write_to_server, NULL, &writeToServer, args) != 0) {
        perror("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }

    pthread_t read_from_server;

    if (pthread_create(&read_from_server, NULL, &readFromServer, args) != 0) {
        perror("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        if (flag) break;
    }
    fprintf(outstream, "The end\n");

    close(sock);
    exit (EXIT_SUCCESS);

}




