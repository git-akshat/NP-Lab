#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd; 
  
    // FIFO file path 
    char * myfifo = "./myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 
  
    char arr1[80], arr2[80]; 
    while (1) 
    { 
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
        
        // enter your message
        printf("You : ");
        fgets(arr2, 80, stdin);
  
        // Write the input arr2 on FIFO 
        // and close it 
        write(fd, arr2, strlen(arr2)+1); 
        close(fd); 
  
        // Open FIFO for Read only 
        fd = open(myfifo, O_RDONLY); 
  
        // Read from FIFO 
        read(fd, arr1, sizeof(arr1)); 
  
        // Print the read message 
        printf("User2: %s", arr1); 
        close(fd); 
    } 
    return 0; 
} 
