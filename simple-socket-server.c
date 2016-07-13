/*
* Name:          Simple Socket Server (in ANSI C)
* Created:       20160629-12:51-GMT+1
*
* Creator:       Kim Olsen <post@kimeriktjoraolsen.no>
* Lastchanhge:   20160701-04:53-GMT+1
*
* Multi-function, simple socket server,
* implemented in ANSI C.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("SimpSockServ: ERROR opening socket\n");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001; /* Port-number to use for socket-server instance */
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("SimpSockServ: ERROR on binding\n");
      exit(1);
   }
      
   /* Now start listening for the clients, here process will
    * go in sleep mode and will wait for the incoming connection
    */
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);	
   if (newsockfd < 0) {
      perror("SimpSockServ: ERROR on accept\n");
      exit(1);
   }
   
   /* If connection is established then start communicating */
   bzero(buffer,256);
   n = read( newsockfd,buffer,255 );   
   if (n < 0) {
      perror("SimpSockServ: ERROR reading from socket\n");
      exit(1);
   }   
   printf("SimpSockServ - Here is the message: %s\n",buffer);
   
   /* Write a response to the client */
   n = write(newsockfd,"I got your message",18);
   if (n < 0) {
      perror("SimpSockServ: ERROR writing to socket\n");
      exit(1);
   }
      
   return 0;
}
