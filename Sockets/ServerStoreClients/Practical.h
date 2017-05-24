//
//  Practical.h
//  
//
//  Created by Tommaso Pino on 23/05/17.
//
//

#ifndef Practical_h
#define Practical_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 255

void DieWithUserMessage(const char *, const char *);
void DieWithSystemMessage(const char *);

void HandleTCPClient(int);

#endif /* Practical_h */
