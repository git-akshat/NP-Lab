/*********************************************************
* Using UDP, write a client – server program,
* to exchange messages between client and the server.
**********************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 8080 
#define MAX 1024 

int main() 
{ 
	int len, n;
	int sockfd; 
	char buffer[MAX]; 
	char *msg; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{ 
		printf("socket creation failed"); 
		exit(-1); 
	} 
	
	// memset(void *address, int value, size_t length);
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	//INADDR_ANY tells the socket to listen on all available interfaces
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		printf("bind failed"); 
		exit(-1); 
	}
	else
	{
		printf("Waiting for message from client...\n");
	}
	 
	while(1)
	{
		n = recvfrom(sockfd, (char *)buffer, MAX, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
		buffer[n] = '\0'; 
		printf("Client : %s", buffer); 
		
		printf("Server : ");
		fgets(msg, MAX, stdin);
		sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	}
		
	return 0; 
} 
