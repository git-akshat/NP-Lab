/* Author : Akshat Agarwal

3. Using TCP/IP sockets, write a client – server program,
    - the client sends the file name and 
    - the server sends back the requested text file if present. */

/* Server Program */

#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sersock, sock, fd, n, reuse = 1;
    char buffer[1024], fname[50];
    
    /* sockfd = socket(domain, type, protocol) */ 
    sersock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };

    // Forcefully connecting to same port everytime
	setsockopt(sersock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));

    /* attaching socket to port */
    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    printf("\nServer is Online");

    listen(sersock, 5); // listen(int sockfd, int backlog)
    sock = accept(sersock, NULL, NULL);

    /*  receive the filename */
    recv(sock, fname, 50, 0);
    printf("\nRequesting for file: %s\n", fname);

    /*  open the file in read-only mode */
    fd = open(fname, O_RDONLY);
    if (fd < 0)
    {
        send(sock, "\nFile not found\n", 15, 0); // strlen(\nFile not found)=15
    }
    else
    {
        while ((n = read(fd, buffer, sizeof(buffer))) > 0)
        {
            send(sock, buffer, n, 0);
        }
    }
    printf("\nFile content sent\n");
    
    close(fd);
    return 0;
}