/* Author : Akshat Agarwal

7.  to implement sliding window protocol, between two hosts(TCP Flow Control)
	- Client sends the frame
	- Server recieves the frame */

/* Server Program */

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
	int sersock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };

	// Forcefully connecting to same port everytime
	int reuse = 1;
	setsockopt(sersock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));

	bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
	printf("\nServer is Online\n");

	listen(sersock, 5);
	int sock = accept(sersock, NULL, NULL);

	char frame[MAX];
	char res[MAX]; // to store all bytes that are recieved successfully
	int ack;
	int k=0;	   // iterator for res
	srand(time(NULL));
	
	while(1) 
	{ 
		int recvsize = 5;
		memset(frame, 0, MAX); // re-initialise frame buffer with 0

		recv(sock, frame, recvsize, 0);  // recv(socket, buffer, length, flag)
		if(strcmp(frame, "Exit") == 0) break; // at end exit frame is recieved 

		if(strlen(frame) < recvsize) 
		{
			recvsize = strlen(frame);
		}
		
		int err_idx = rand()%8; // probability of byte to get corrupted = 50%
		if(err_idx < recvsize)
		{
			recvsize = err_idx;
			frame[err_idx]='x';
			printf("\nError occured at = %d", err_idx+1);
		}

		strncpy(res+k , frame , recvsize);
        	k+=recvsize ;
		
		printf("\nPacket received  = %s", frame);
		printf("\nReceiving window: ");
		printf("\n start seqno = %d", k-recvsize);
		printf("\n end seqno   = %d", k-1);

		ack = k ;
		printf("\nSending ack = %d", ack);
		send(sock, &ack, sizeof(ack), 0) ;  
		printf("\n");
	}

	res[k] = '\0';
	printf("\n\nFinal string recieved at Destination = ");
	fputs(res, stdout);

	printf("\n\n");
	close(sock); close(sersock);
}

/*
Server is Online

Error occured at = 4
Packet received  = thix 
Receiving window: 
 start seqno = 0
 end seqno   = 2
Sending ack = 3

Error occured at = 4
Packet received  = s ix 
Receiving window: 
 start seqno = 3
 end seqno   = 5
Sending ack = 6

Error occured at = 2
Packet received  = sxmy 
Receiving window: 
 start seqno = 6
 end seqno   = 6
Sending ack = 7

Error occured at = 4
Packet received  =  myxh
Receiving window: 
 start seqno = 7
 end seqno   = 9
Sending ack = 10

Error occured at = 3
Packet received  =  hxus
Receiving window: 
 start seqno = 10
 end seqno   = 11
Sending ack = 12

Error occured at = 3
Packet received  = ouxe
Receiving window: 
 start seqno = 12
 end seqno   = 13
Sending ack = 14

Packet received = se
Receiving window: 
 start seqno = 14
 end seqno   = 15
Sending ack = 16


Final string recieved at Destination = this is my house
*/
