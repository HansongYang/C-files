#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void createSocket(int*);
void SetupServerAddress(struct sockaddr_in*);
void chat(char*, int, int, struct sockaddr_in, struct sockaddr_in);
void wait(struct sockaddr_in, int*, int);
void talk(int,int,int);
void SetupUserAddress(struct sockaddr_in*, char*);
void closeSocket(int, int);
