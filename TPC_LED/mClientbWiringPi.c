/* A simple client program to interact with the myServer.c program on the Raspberry.
 myClient.c
 D. Thiebaut
 Adapted from http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
 The port number used in 51717.
 This code is compiled and run on the Macbook laptop as follows:
 
 g++ -o myClient myClient.c
 ./myClient
 
 
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void error(char *msg) {
  perror(msg);
  exit(0);
}
char* errorString;

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

int main(int argc, char *argv[])
{
  int sockfd, portno = 51717, n;
  char serverIp[] = "192.168.1.110";
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  int data;
  char line[256];
  int c;
  
  if (argc < 3) {
    // error( const_cast<char *>( "usage myClient2 hostname port\n" ) );
    printf( "contacting %s on port %d\n", serverIp, portno );
    // exit(0);
  }
  if ( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
  {
    errorString = "ERROR opening socket";
    error( errorString );
  }
  
  if ( ( server = gethostbyname( serverIp ) ) == NULL )
  {
    errorString = "ERROR, no such host\n";
    error( errorString );
  }
  
  bzero( (char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
  {
    errorString = "ERROR connecting";
    error( errorString );
  }
  
  while(1) {
    
    printf( "turn on the LED? yes/no 1/0\n");
    if(fgets(line, sizeof(line), stdin)!=NULL)
    {
      sscanf(line, "%d", &c);
      printf("%d\n",c );
      switch(c)
      {
        case(1):
          printf("sending ...\n");
          sendData( sockfd, 1 );
          printf("sent\n");
          break;
        case(0):
          printf("sending ...\n");
          sendData( sockfd, 0 );
          printf("sent\n");
          break;
        case(-2):
          printf("sending ...\n");
          sendData( sockfd, -2 );
          printf("sent\n");
          break;
      }
      //printf("getting ...\n");
      //data = getData( sockfd );
      //printf("got\n");
      
      //printf("The LED is (ON/OFF) (1/0): %d\n",data );
      if (c<0)
        break;
    }

  }
  
  close( sockfd );
  return 0;
}
