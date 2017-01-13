#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>



#define MY_PORT 60002


void createSocket(int*);

void SetupServerAddress(struct sockaddr_in*);

void chat(char*, int, int, struct sockaddr_in, struct sockaddr_in);

void wait(struct sockaddr_in, int*, int);

void talk(int,int,int);

void SetupUserAddress(struct sockaddr_in*, char*);

void closeSocket(int, int);

int main(){

	int mySocket, otherSocket;

	struct sockaddr_in  myAddr, otherAddr;

	char commands[80];

	createSocket(&mySocket);

	chat(commands, mySocket, otherSocket, myAddr, otherAddr);

	return 0;

}

/*

    Function:  creatSocket

     Purpose:  creat the socket

	  In:  mySocket

*/

void createSocket(int* mySocket){

	*mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(*mySocket < 0){

		printf("Could not open socket.");

		exit(-1);

	}

}



/*

    Function:  SetupServerAddress

     Purpose:  set up the server address

	  In:  myAddr

*/

void SetupServerAddress(struct sockaddr_in  *myAddr){

	memset(myAddr, 0, sizeof(*myAddr));

	myAddr->sin_family = AF_INET;

	myAddr->sin_addr.s_addr = htonl(INADDR_ANY);

	myAddr->sin_port = htons((unsigned short) MY_PORT);

}



/*

    Function:  SetupUserAddress

     Purpose:  set up the user address

	  In:  myAddr

*/

void SetupUserAddress(struct sockaddr_in  *myAddr, char* USER_IP){

	memset(myAddr, 0, sizeof(*myAddr));

  	myAddr->sin_family = AF_INET;

  	myAddr->sin_addr.s_addr = inet_addr(USER_IP);

  	myAddr->sin_port = htons((unsigned short) MY_PORT);

}





/*

    Function:  chat

     Purpose:  let the user enter the chat feature and enter commands

	  In:  commands

	  In:  mySocket

	  In:  otherSocket

	  In:  myAddr

	  In:  otherAddr

*/

void chat(char* commands, int mySocket, int otherSocket, struct sockaddr_in  myAddr, struct sockaddr_in otherAddr){

    	int server = -1;

	int i;

	printf("Hello there. You have entered the chat feature.\n");

	while(1){

		printf("There are four commands that you can enter. 1. wait 2. talk 3. close 4. exit.\n");

		scanf("%s", commands);

		if(strcmp(commands, "wait") == 0){

			createSocket(&mySocket);

			SetupServerAddress(&myAddr);



			i = bind(mySocket,(struct sockaddr *) &myAddr,sizeof(myAddr));

			if(i<0){printf("Sorry, couldn't bind socket!\n"); continue;}



			i = listen(mySocket,5);

			if(i<0){ printf("Sorry, couldn't listen.\n"); continue;}



			wait(otherAddr, &otherSocket, mySocket);

			server = 1;

			talk(server,mySocket,otherSocket);

		}

		else if(strcmp(commands, "talk") == 0){

			createSocket(&mySocket);

			char address[10];

			printf("Please enter your IP address:  ");

			scanf("%s", address);



			SetupUserAddress(&myAddr, address);

			if(connect(mySocket,(struct sockaddr *) &myAddr,sizeof(myAddr))<0){

 				printf("Sorry, couldn't accept the connection.\n");

				continue;

			}

			server = 0;

			talk(server,mySocket,otherSocket);

		}

		else if(strcmp(commands, "close") == 0){

			closeSocket(mySocket, otherSocket);

		}

		else if(strcmp(commands, "exit") == 0){

            		printf("Bye bye. See you next time.\n");

			break;

		}

		else{

			printf("Sorry, invalid input.\n");

		}

	}

}



/*

    Function:  wait

     Purpose:  wait for connection with other user

	  In:  otherAddr

	  In:  otherSocket

	  In:  mySocket

*/

void wait(struct sockaddr_in otherAddr, int* otherSocket, int mySocket){

	int addrSize = sizeof(otherAddr);

	*otherSocket = accept(mySocket, (struct sockaddr *) &otherAddr, &addrSize);

	if(otherSocket < 0){

		printf("Sorry. The connection hasn't built up.\n");

		exit(-1);

	}

}



/*

    Function:  closeSocket

     Purpose:  close the socket

	  In:  mySocket

	  In:  otherSocket

*/



void closeSocket(int mySocket, int otherSocket){

	close(mySocket);

	close(otherSocket);

}



/*

    Function:  talk

     Purpose:  send and receive message

	  In:  server

	  In:  mySocket

	  In:  otherSocket

*/

void talk(int server,int mysocket,int otherSocket)

{

 	char buf[80];

	int buf_len=0, sendbytes=0, recvbytes=0;



	printf("\n");

	printf("Welcome to the talk mode, now you can talk with somebody.\n");

	printf("\n");



        if(server==1){

        //server

        while(1){

		printf("Waiting for message........\n");

		if((recvbytes = recv(otherSocket ,buf,80,0)) == -1){

			printf("Fail to receive message.\n");

			 exit(1);

		}

		 else{

		  buf[recvbytes] = 0;

		  if(!strncmp(buf,"close",5)){

			break;

		}



		   if(strlen(buf) > 1){

		  	printf("The other user said:  %s\n",buf);

			}

		}



		printf("What's your message?\n");

		fgets(buf,80,stdin);

		buf_len = sizeof(buf);

		if((sendbytes = send(otherSocket ,buf,buf_len,0))==-1){

			printf("Fail to send message.\n");

			exit(1);

		}

		if(!strncmp(buf,"close",5)){

			break;

		}

       	}

   }

    else{

        //client

       while(1){

		printf("What's your message? \n");

		fgets(buf,80,stdin);

		buf_len = sizeof(buf);

		if((sendbytes = send(mysocket ,buf,buf_len,0))==-1){

			printf("Fail to send message.\n");

			exit(1);

		}

		if(!strncmp(buf,"close",5)){

			break;

		}



		printf("Waiting for message........\n");

		if((recvbytes = recv(mysocket ,buf,80,0))==-1){

			printf("Fail to receive message.\n");

			 exit(1);

		}

		 else{

		  buf[recvbytes] = 0;

		  if(strlen(buf) > 1){

		 	 printf("The other user said:  %s\n",buf);

			}



		  if(!strncmp(buf,"close",5)){

			break;

			}

		}

	}

    }

}
