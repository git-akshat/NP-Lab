/* Author : Akshat Agarwal

6. Write a socket program to demonstrate ip multicasting which provides the capability for an application to send IP datagram that a group of hosts in anetwork can receive. */

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
    int sock;
    char msg[1024];
    struct sockaddr_in groupaddr;
    struct in_addr localInterface;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&groupaddr, 0, sizeof(groupaddr));
    groupaddr.sin_family = AF_INET;
    groupaddr.sin_addr.s_addr = inet_addr("226.1.1.1");
    groupaddr.sin_port = htons(1234);

    localInterface.s_addr = INADDR_ANY;  // or system ip address
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));

    printf("Enter message : ");
    fgets(msg, 1024, stdin);
    msg[strlen(msg)-1] = '\0'; // to remove '\n' from string
    sendto(sock, msg, sizeof(msg), 0, (struct sockaddr*)&groupaddr, sizeof(groupaddr));
    printf("Message Sent.\n");
            
    return 0;
}