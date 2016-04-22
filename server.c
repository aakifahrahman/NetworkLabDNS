#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
	
	int udpSocket, nBytes;
	char buffer[1024], hostname[40], hostfile[40], ipfile[40], linefile[82];
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	int i, j, k, l, m, n, equal=0, found=0;
	
	udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (udpSocket == -1){
		printf("Error creating socket !\n");
		exit(0);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9025);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	if (bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1){
		printf("Error in binding !\n");
		exit(0);
	}
	else
		printf("Waiting to recieve UDP packets...\n");

	addr_size = sizeof serverStorage;

		
		nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
		if (nBytes <= 0){
			printf("Error in recieving !\n");
			exit(0);
		}
		else
			printf("A UDP Packet recieved !\n");


		for(i=0;i<nBytes-1;i++){
			if(buffer[i] == ' ')
				break;
		}
		i++;
		k=0;
		for(;i<nBytes-1;i++,k++){
			if(buffer[i] != '\0')
				hostname[k]=buffer[i];
			else
				break;
		}
		hostname[k]='\0';
		
		FILE *fp = fopen("test.txt","r");
		if(fp == NULL){
			printf("Error in opening file !");
			exit(0);
		}

		while(fgets(linefile, 82, fp) != NULL){
			found=0;
			equal=0;
			for(j=0; j<40; j++){
				if(linefile[j] != ' ')
					hostfile[j]=linefile[j];
				else
					break;
			}
			hostfile[j]='\0';
			
			m=0;
			for(l=j+1; l<40;l++,m++){
				if(linefile[l] != '\0')
					ipfile[m]=linefile[l];
				else
					break;
			}
			ipfile[m]='\0';
			
			for(n=0;n<k-1;n++){
				if(hostname[n] != hostfile[n])
					break;
			}
			if (n == (k-1)) equal = 1;
			if(equal == 1){
				found=1;			
				if (sendto(udpSocket,ipfile,m-1,0,(struct sockaddr *)&serverStorage,addr_size) == -1){
					printf("Error in sending IP address !\n");
					exit(0);
				}
				else
					printf("IP adress sent successfully !\n");
				break;
			}
		}

		if(found == 0){
			printf("IP address not found !\n");
			char notfound[3];
			strcpy(notfound,"no");
			if (sendto(udpSocket,notfound,2,0,(struct sockaddr *)&serverStorage,addr_size) == -1){
					printf("Error in sending error message !\n");
					exit(0);
			}
		} 

	return 0;

}
