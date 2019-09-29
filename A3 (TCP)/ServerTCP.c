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
    int server_fd, sock, fd, n;
    char buffer[1024], fname[50];
    struct sockaddr_in addr;

    /* creating socket file descriptor */
    /* sockfd = socket(domain, type, protocol) */ 
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    /* htons() converts the unsigned short integer
    ** from host byte order to network byte order.
    */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* attaching socket to port */
    /* bind(sockfd, addr , addrlen) */
    bind(server_fd, (struct sockaddr *) &addr, sizeof(addr));
    printf("\nServer is Online");

    /* listen for connections from the socket */
    /* listen(int sockfd, int backlog) */
    listen(server_fd, 5);

    /* accept a connection, we get a file descriptor */
    /* new_socket = accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) */
    sock = accept(server_fd, NULL, NULL);

    /*  receive the filename */
    /* recv(int socket, const void *buffer, size_t length, int flags); */
    recv(sock, fname, 50, 0);
    printf("\nRequesting for file: %s\n", fname);

    /*  open the file in read-only mode */
    fd = open(fname, O_RDONLY);

    if (fd < 0)
    {
        send(sock, "\nFile not found\n", 15, 0);
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