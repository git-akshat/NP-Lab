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
	int n, len;
	int sockfd; 
	char buffer[MAX]; 
	char *msg; 
	struct sockaddr_in servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{ 
		printf("socket creation failed"); 
		exit(-1); 
	}

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	while(1)
	{
		printf("Client : ");
		fgets(msg, MAX, stdin); 
		sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
			
		n = recvfrom(sockfd, (char *)buffer, MAX, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
		buffer[n] = '\0'; 
		printf("Server : %s", buffer); 
	}

	return 0; 
} 
