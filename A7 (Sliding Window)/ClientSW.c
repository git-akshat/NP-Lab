/**************************************************
* Program to implement sliding window protocol,
  between two hosts(TCP Flow Control)
* Client sends the packet
* Server recieves the packet 
***************************************************/

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
    int sock, ack; 
    char msg[MAX], frame[MAX]; 
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); // PORT = 1234
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /*  keep trying to establish connection with server */
    while(connect(sock, (struct sockaddr *) &addr, sizeof(addr))) ;

    printf("\nClient is connected to Server\n");

    printf("\nEnter message to send : ");
    scanf("%s", msg);

    int i = 0;
    while(i<strlen(msg)) 
    { 
        int sendsize = 5;

        // memset(starting_addr , value , length)
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

        // send(socket, buffer, length, flag)
        send(sock, frame, strlen(frame), 0); 
        printf("\nData sent. Waiting for ack...");

        // recv(socket, buffer, length, flag)
        recv(sock, &ack, sendsize, 0); 
        printf("\nreceived ack no = %d ",ack);  

        // next data seq no = incoming ack no
        i = ack;
    }

    send(sock, "Exit", strlen("Exit"), 0); 
    printf("\n\n");

    close(sock);
}