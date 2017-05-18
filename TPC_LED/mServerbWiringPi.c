/* A simple server in the internet domain using TCP.
myServer.c
D. Thiebaut
Adapted from http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
The port number used in 51717.
This code is compiled and run on the Raspberry as follows:
   
    g++ -o myServer myServer.c 
    ./myServer

The server waits for a connection request from a client.
The server assumes the client will send positive integers, which it sends back multiplied by 2.
If the server receives -1 it closes the socket with the client.
If the server receives -2, it exits.
*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wiringPi.h>

char* errorString;

void error( char *msg ) {
  perror(  msg );
  exit(1);
}

int func( int a ) {
   return 2 * a;
}

void sendData( int sockfd, int x ) {
  int n;

  char buffer[32];
  sprintf( buffer, "%d\n", x );
  if ( (n = write( sockfd, buffer, strlen(buffer) ) ) < 0 )
  {
    errorString = "ERROR writing to socket";
    error( errorString );
  }
  buffer[n] = '\0';
}

int getData( int sockfd ) {
  char buffer[32];
  int n;

  if ( (n = read(sockfd,buffer,31) ) < 0 )
  {
    errorString = "ERROR reading from socket";
    error( errorString );
  }
  buffer[n] = '\0';
  return atoi( buffer );
}

int main(int argc, char *argv[]) {
     int sockfd, newsockfd, portno = 51717, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     int data;
  const int pressed = 1;
  const int realised = 0;
  int status, stsButton;
  int valueNew, valueOld;
  valueNew = 0;
  valueOld = 0;
  stsButton = 0;
    printf( "set up wiringPi\n");
    wiringPiSetup () ;
    pinMode (0, OUTPUT) ;
    pinMode (1, INPUT ) ;
     printf( "using port #%d\n", portno );
    
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
     {
       errorString = "ERROR opening socket";
       error( errorString );
     }
     bzero((char *) &serv_addr, sizeof(serv_addr));

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons( portno );
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
     {
       errorString = "ERROR on binding";
       error( errorString );
     }
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
  
     //--- infinite wait on a connection ---
     while ( 1 ) {
        printf( "waiting for new client...\n" );
        if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
        {
          errorString = "ERROR on accept";
          error( errorString );
        }
       
        data = getData( newsockfd );
        if(data == -2)
        {
          close( newsockfd );
          break;
        }
        printf( "recived #%d\n", data );

        //--- if -2 sent by client, we can quit ---
        switch(data)
        {
          case(1):
            digitalWrite(0,HIGH);
            sendData( newsockfd, data );
            break;
          case(0):
            digitalWrite(0,LOW);
            sendData( newsockfd, data );
            break;
         }
       
       close( newsockfd );
         printf( "opened new communication with client\n" );
       }
     return 0; 
}
