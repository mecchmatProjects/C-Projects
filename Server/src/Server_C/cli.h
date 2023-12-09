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

///type for arguments to pass in thread creating function
typedef struct {
    FILE * instream;
    FILE * outstream;
}InputOutput;


void cli(FILE * instream, FILE * outstream);
/** @brief main initializing function of tcp client
*
*   @param stream for input username and messages
*   @param stream for output messages about runtime actions
*/


void * writeToServer (void *arg);
/** @brief This function get user input and send messages to server.
*
*   running in separate thread
*   @param pointer to InputOutput structure
*/ 




void * readFromServer (void *arg);
/** @brief This function read messages from server and output them.
*
*   running in separate thread
*   @param pointer to InputOutput structure
*/ 


void catch_ctrl_c_and_exit(int sig);
/** @brief handler for signal
*/

#endif 
