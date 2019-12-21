/* Author : Akshat Agarwal

7.  to implement sliding window protocol, between two hosts(TCP Flow Control)
	- Client sends the frame
	- Server recieves the frame */

/* Client Program */

#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#include<unistd.h>
#include<sys/socket.h> 
#include<sys/types.h> 
#include<arpa/inet.h> 

#define MAX 20

int main() 
{ 
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };

    /*  keep trying to establish connection with server */
    while(connect(sock, (struct sockaddr *) &addr, sizeof(addr))) ;
    printf("\nClient is connected to Server\n");

    char msg[MAX];
    printf("\nEnter message to send : ");
    fgets(msg, MAX, stdin);
    msg[strlen(msg)-1] = '\0';

    char frame[MAX];
    int i = 0;
    int ack; 
    
    while(i<strlen(msg)) 
    { 
        int sendsize = 5;
        memset(frame, 0, MAX); // re-initialise frame buffer with 0

        // strncpy(destination , source , length)
        strncpy(frame, msg+i, sendsize); //copy msg to frame
        if( sendsize > strlen(frame) )
        {
            sendsize = strlen(frame);
        }
        printf("\n\nSending packet = %s", frame);
        printf("\nSending window: ");
        printf("\n start seqno = %d", i);
        printf("\n end seqno   = %d", i+sendsize-1);

        send(sock, frame, sendsize, 0);
        recv(sock, &ack, sizeof(ack), 0); 
        printf("\nreceived ack no = %d ",ack);  

        i = ack; // next data seq no = incoming ack no
    }
    send(sock, "Exit", strlen("Exit"), 0); 
    close(sock); printf("\n\n");
}

/*
Client is connected to Server

Enter message to send : this is my house

Sending packet = this 
Sending window: 
 start seqno = 0
 end seqno   = 4
received ack no = 3 

Sending packet = s is 
Sending window: 
 start seqno = 3
 end seqno   = 7
received ack no = 6 

Sending packet = s my 
Sending window: 
 start seqno = 6
 end seqno   = 10
received ack no = 7 

Sending packet =  my h
Sending window: 
 start seqno = 7
 end seqno   = 11
received ack no = 10 

Sending packet =  hous
Sending window: 
 start seqno = 10
 end seqno   = 14
received ack no = 12 

Sending packet = ouse
Sending window: 
 start seqno = 12
 end seqno   = 15
received ack no = 14 

Sending packet = se
Sending window: 
 start seqno = 14
 end seqno   = 15
received ack no = 16 
*/