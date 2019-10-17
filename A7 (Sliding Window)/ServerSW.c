/**************************************************
* Program to implement sliding window protocol,
  between two hosts(TCP Flow Control)
* Client sends the frame
* Server recieves the frame 
***************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h> 
#include<arpa/inet.h> 

#define MAX 20

int main() 
{ 
	int server_fd, sock; 
	char frame[MAX];
	char res[MAX]; // to store all bytes that are recieved successfully
	struct sockaddr_in addr;
	int ack;

	/* creating socket file descriptor */
	server_fd = socket(AF_INET, SOCK_STREAM, 0); // sockfd = socket(domain, type, protocol)
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234); 
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* attaching socket to port */
	bind(server_fd, (struct sockaddr *) &addr, sizeof(addr));
	printf("\nServer is Online");

	/* listen(fd, backlog) */
	listen(server_fd, 5); // listen for connections from client

	/* new_sock = accept(int fd, addr, addrlen) */
	sock = accept(server_fd, NULL, NULL);

	int k=0; // iterator for res[MAX]
	srand(time(NULL));
	
	while(1) 
	{ 
		int recvsize = 5;
		memset(frame, 0, MAX); // re-initialise frame buffer with 0

		// recv(socket, buffer, length, flag)
		recv(sock, frame, recvsize, 0); 

		if(strlen(frame) < recvsize) 
		{
			recvsize = strlen(frame);
		}
		// at end exit frame is recieved from client
		if(strcmp(frame, "Exit") == 0) break;
		
		int err_idx = rand()%8; // probability of byte to get corrupted = 50%
		int j;

		if(err_idx < recvsize)
		{
			for(j=0; j<err_idx ; j++)
			{
				res[k++] = frame[j];
			}
			frame[err_idx]='x';
			printf("\n\nPacket received = %s", frame);
			printf("\nError at byte   = %d", err_idx+1);
			printf("\nReceiving window: ");
			printf("\n start seqno = %d", k-err_idx);
		}
		else
		{ 
			for(j=0; j<recvsize ; j++)
			{
				res[k++] = frame[j];
			}
			printf("\n\nPacket received = %s", frame);
			printf("\nReceiving window: ");
			printf("\n start seqno = %d", k-recvsize);
		}
		printf("\n end seqno   = %d", k-1);
		ack = k ;
		printf("\nSending ack = %d", ack);
		send(sock, &ack, sizeof(ack), 0) ;  
	}
	res[k] = '\0';
	printf("\n\nFinal string recieved at Destination = ");
	fputs(res, stdout);

	printf("\n\n");
	close(sock);
	close(server_fd);
}