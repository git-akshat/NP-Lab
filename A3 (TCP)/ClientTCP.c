/*********************************************************
* Using TCP/IP sockets, write a client – server program,
* the client sends the file name and 
* the server sends back the requested text file if present.
**********************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int soc, n;
    char buffer[1024], fname[50];
    struct sockaddr_in addr;

    /* socket creates an endpoint for communication */
    /* sockfd = socket(domain, type, protocol) */ 
    soc = socket(AF_INET, SOCK_STREAM, 0);

    /* sockaddr_in is used for ip manipulation
     * we define the port and IP for the connection. */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /*  keep trying to esatablish connection with server */
    while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ;
    
    printf("\nClient is connected to Server");

    printf("\nEnter file name: ");
    scanf("%s", fname);

    /* send the filename to the server */
    /* send(int socket, const void *buffer, size_t length, int flags); */
    send(soc, fname, sizeof(fname), 0);

    printf("\nRecieved file data\n");
    printf("---------------------------------------------------------\n");

    /*  keep printing any data received from the server */
    while ((n = recv(soc, buffer, sizeof(buffer), 0)) > 0)
    {
        printf("%s", buffer);
    }
    
	printf("---------------------------------------------------------\n");
	
    return 0;
}
