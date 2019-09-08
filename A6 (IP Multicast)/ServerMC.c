/************************************************************
* Write a socket program to demonstrate ip multicasting 
* which provides the capability for an application to send
* IP datagram that a group of hosts in anetwork can recieve.
*************************************************************/

/**** server sends the message ****/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main ()
{
	int sockfd;
	char msg[1024];
	struct sockaddr_in groupaddr;
    struct in_addr localInterface;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
      printf("Datagram socket error");
      exit(1);
    }
     
    memset(&groupaddr, 0, sizeof(groupaddr));

    groupaddr.sin_family = AF_INET;
    groupaddr.sin_addr.s_addr = inet_addr("226.1.1.1");
    groupaddr.sin_port = htons(1234);

    /* Set local interface for outbound multicast datagrams. */
    /* localInterface.s_addr = inet_addr("your system ip address") */
    localInterface.s_addr = INADDR_ANY; 
    if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
    {
        printf("Setting local interface error");
        exit(1);
    }
    
    printf("Enter message : ");
    fgets(msg, 1024, stdin);
    msg[strlen(msg)-1] = '\0'; // to remove '\n' from string
	
    sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&groupaddr, sizeof(groupaddr));
    printf("Message Sent.\n");
    	  
    return 0;
}