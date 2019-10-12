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
	int n, len, sockfd;
	char buffer[MAX]; 
	char *msg; 
	struct sockaddr_in servaddr; 

	// Creating socket file descriptor 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&servaddr, 0, sizeof(servaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	while(1)
	{
		printf("Client : ");
		fgets(msg, MAX, stdin); 
		sendto(sockfd, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
			
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, NULL, NULL); 
		buffer[n] = '\0'; 
		printf("Server : %s", buffer); 
	}
	return 0; 
} 