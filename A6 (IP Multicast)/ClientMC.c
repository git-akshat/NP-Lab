/* Author : Akshat Agarwal

6. Write a socket program to demonstrate ip multicasting which provides the capability for an application to send IP datagram that a group of hosts in a network can receive. */

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
	int sock, reuse = 1;
	char msg[1024];
	struct sockaddr_in addr;
	struct ip_mreq group;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = INADDR_ANY; // to listen on all available interfaces.

	bind(sock, (struct sockaddr*)&addr, sizeof(addr));

	group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
	group.imr_interface.s_addr = inet_addr("127.0.0.1");
	setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));
	printf("Waiting for message from server.....");

	// recvfrom(sock, msg, sizeof(msg), 0, NULL, NULL);
	read(sock, msg, sizeof(msg));
	printf("\nThe message from multicast server is : %s \n", msg);

	close(sock);
	return 0;
}