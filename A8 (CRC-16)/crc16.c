/* Author : Akshat Agarwal

8. Write a program for Error Detection using CRC-CCITT(16 bits). */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAX 30

/* crc(dividend , divisor, remainder) */
void crc(char *data, char *gen, char *rem)
{
    int i, j, lengthDiff = strlen(data)-strlen(gen) ; 
    char out[MAX]; // xored val after each step

    strcpy(out, data);

    /* Perform XOR on the msg */
    for(i=0; i<lengthDiff +1 ; i++)
    {
        if(out[i]=='0') continue ; 
        out[i] = '0' ;
        for(int j = 1 ; j<strlen(gen) ; j++){
            out[i+j] = (gen[j]==out[i+j] ?'0':'1') ; 
        }
    }

    // size of output = strlen(gen)-1 = 16 bits 
    strncpy(rem , out+lengthDiff+1 , strlen(gen)-1);
    rem[strlen(gen)-1] = '\0' ;
}

int main()
{
    int i, j;
    char dword[MAX]; // dataword
    char augWord[MAX]; // augmented dataword
    char cword[MAX]; // codeword
    char rem[MAX]; // remainder from crc
    char recv[MAX]; // received message 
    char gen[MAX] = "10001000000100001\0";

    printf("\nCRC-16 Generator : x^16 + x^12 + x^5 + 1 ");
    printf("\nBinary Form      : %s", gen);

    printf("\n\nEnter Dataword   : ");
    scanf("%s", dword);

    strcpy(augWord, dword);
    for(i=0; i<strlen(gen)-1; i++)
    {
        strcat(augWord, "0");
    }
    printf("\nAugmented dataword is   : %s",augWord);

    crc(augWord, gen, rem);

    strcpy(cword, dword);
    strcat(cword, rem);
    printf("\n\nFinal data transmitted  : %s", cword);

    printf("\n\nEnter the data received : ");
    scanf("%s", recv);
    if(strlen(recv) < strlen(cword))
    {
        printf("\n Invalid input \n");
        exit(0);
    }

    crc(recv, gen, rem);

    printf("\nSyndrome = %s ", rem);
    
    if(strstr( rem , "1")!=0)
   {
        printf("\nError occured !!! Corrupted data received. \n");
        exit(0);
    }
    printf("\nNo Error. Data received successfully.\n");
}

/*************** Output -1 *************************
CRC-16 Generator : x^16 + x^12 + x^5 + 1
Binary Form      : 10001000000100001

Enter Dataword   : 11110001

Augmented dataword is   : 111100010000000000000000

Final data transmitted  : 111100011111111100111110

Enter the data received : 111100011111111100111110

Syndrome = 0000000000000000
No Error. Data received successfully.
*****************************************************/

/*************** Output -2 *************************
CRC-16 Generator : x^16 + x^12 + x^5 + 1
Binary Form      : 10001000000100001

Enter Dataword   : 10101011

Augmented dataword is   : 101010110000000000000000

Final data transmitted  : 101010110000010010000001

Enter the data received : 101010110000000000000000

Syndrome = 0000010010000001
Error occured !!! Corrupted data received.
*****************************************************/
