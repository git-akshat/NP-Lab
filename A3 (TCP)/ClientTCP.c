/* Author : Akshat Agarwal

3. Using TCP/IP sockets, write a client – server program,
    - the client sends the file name and 
    - the server sends back the requested text file if present. */

/* Client Program */

#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock, n;
    char buffer[1024], fname[50];

    /* sockfd = socket(domain, type, protocol) */ 
    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };

    /*  keep trying to esatablish connection with server */
    while(connect(sock, (struct sockaddr *) &addr, sizeof(addr))) ;
    printf("\nClient is connected to Server");

    /* send the filename to the server */
    printf("\nEnter file name: ");
    scanf("%s", fname);
    send(sock, fname, sizeof(fname), 0);

    printf("\nRecieved file data\n");
    printf("---------------------------------------------------------\n");

    /*  keep printing any data received from the server */
    while ((n = recv(sock, buffer, sizeof(buffer), 0)) > 0)
    {
	buffer[n] = '\0' ;
        printf("%s", buffer);
    }
    
	printf("---------------------------------------------------------\n");
	
    return 0;
}
