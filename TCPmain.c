#include "TCPDefs.h"


int main(){
	int mySocket, otherSocket;
	struct sockaddr_in  myAddr, otherAddr;
	char commands[80];
	createSocket(&mySocket);
	chat(commands, mySocket, otherSocket, myAddr, otherAddr);
	return 0;
}
