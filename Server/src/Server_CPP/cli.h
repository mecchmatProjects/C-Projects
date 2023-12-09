/**  @file cli.h
*    @brief declaration of methods and headers for client part.
*    
*    
*    
*
*    @author Kekalo Kateryna
*/


#ifndef CLI_H
#define CLI_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <locale.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



#define SERVER_PORT 5555
#define SERVER_NAME "127.0.0.1"
#define BUFLEN 512

void client();
/** @brief main initializing function of tcp client
*
*/


void * writeToServer (void *arg);
/** @brief This function get user input and send messages to server.
*
*   running in separate thread
*/ 

void * readFromServer (void *arg);
/** @brief This function read messages from server and output them.
*
*   running in separate thread
*/ 



void catch_ctrl_c_and_exit(int sig);

#endif 
