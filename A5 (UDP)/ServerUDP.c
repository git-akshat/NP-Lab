/* Author : Akshat Agarwal

5. Using UDP, write a client–server program, to exchange messages between client and the server. */

/* Server Program */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define MAX 1024 

int main() 
{ 
	char buffer[MAX], msg[MAX]; 
	struct sockaddr_in servaddr, cliaddr; 
	 
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	// Forcefully connecting to same port everytime
	int reuse = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	
	// Initialize servaddr and cliaddr with zero
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	int len = sizeof(cliaddr);
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY listen on all available interfaces
	servaddr.sin_port = htons(1234); 
	
	// Bind the socket with the server address 
	bind(sock, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("Waiting for message from client...\n");
	 
	while(1)
	{
		int n = recvfrom(sock, (char *)buffer, sizeof(buffer), 0, ( struct sockaddr *) &cliaddr, &len); 
		buffer[n] = '\0'; 
		printf("Client : %s", buffer); 
		
		printf("Server : ");
		fgets(msg, MAX, stdin);
		sendto(sock, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &cliaddr, len);
	}
	return 0; 
} 