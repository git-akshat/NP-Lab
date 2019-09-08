/************************************************************
* Write a socket program to demonstrate ip multicasting 
* which provides the capability for an application to send
* IP datagram that a group of hosts in anetwork can recieve.
*************************************************************/

/**** clients recieves the message ****/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	int sockfd;
	char msg[1024];
	struct sockaddr_in addr;
	struct ip_mreq group;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		printf("Opening datagram socket error");
		exit(1);
	}

	int reuse = 1;
	// Enable SO_REUSEADDR to allow multiple instances of this application to receive copies of the multicast datagrams.
	// When level = SOL_SOCKET, the item will be searched for in the socket itself.
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
	{
		printf("Setting reuse address error");
		close(sockfd);
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY tells the socket to listen on all available interfaces.

	if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		printf("Binding failed");
		close(sockfd);
		exit(1);
	}

	group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
	group.imr_interface.s_addr = INADDR_ANY; // group.imr_interface.s_addr = inet_addr("your system ip address")
	if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
	{
		printf("Adding multicast group error");
		close(sockfd);
		exit(1);
	}	
	printf("Waiting for message from server.....");

	read(sockfd, msg, sizeof(msg));
	printf("\nThe message from multicast server is : %s \n", msg);

	close(sockfd);
	return 0;
}