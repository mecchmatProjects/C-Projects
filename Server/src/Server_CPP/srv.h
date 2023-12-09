/**  @file cli.h
*    @brief declaration of methods and headers for server part.
*    
*    
*    
*
*    @author Kekalo Katerynas
*/


#ifndef SRV_H
#define SRV_H

#define _DEFAULT_SOURCE
#include <poll.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>



#define SERVER_PORT 5555
#define BUFLEN 512
#define N_CLIENTS 200
#define TEMPFILENAME ".tmp.txt"


int server();
/** @brief main initializing function of tcp server
*/


void writeToClient (int fd, char *buf);
int readFromClient (int fd, char *buf);
void resend(int fd, char * cli_id);
/** @brief function which check whether there are not messages for 
*	  client with cli_id username and send them
*
*	  @param number of file descriptor
*	  @param username of client
*/

int find_client(char * buf, char clients[][BUFLEN], int n_clients);
/** @brief find user to which msg in buf was sent
*
*  @param message
*  @param list of usernames
*  @param length of list 
*/


#endif
