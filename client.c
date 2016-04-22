#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){

	int clientSocket, portNum, nBytes;
	char buffer1[1024], buffer2[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (clientSocket == -1){
		printf("Error creating socket !\n");
		exit(0);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9025);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof serverAddr;

		printf("Type a command (of the form 'nslook abc.com') :\n");
		fgets(buffer1,1024,stdin);

		nBytes = strlen(buffer1) + 1;
		if (sendto(clientSocket,buffer1,nBytes,0,(struct sockaddr *)&serverAddr,addr_size) == -1){
			printf("Error in sending command !\n");
			exit(0);
		}
		else 
			printf("Sending packet successful !\n");

		nBytes = recvfrom(clientSocket,buffer2,1024,0,NULL, NULL);
		if (nBytes <= 0){
			printf("Error in recieving !\n");
			exit(0);
		}
		else
		if(buffer2[0]=='n' && buffer2[1]=='o')
			printf("IP Address not found !\n");
		else
			printf("IP Address received from server: %s\n",buffer2);

	return 0;
}
