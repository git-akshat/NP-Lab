# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAX 30

/* crc(dividend , divisor, remainder) */
void crc(char *data, char *gen, char *rem)
{
    int i, j, k=0;
    char out[MAX]; // xored val after each step

    strcpy(out, data);

    /* Perform XOR on the msg */
    for(i=0; i<strlen(data)-strlen(gen)+1; i++)
    {
        if(out[i] == '1')
        {
            for(j=1; j<strlen(gen); j++)
            {
                out[i+j] = (out[i+j] == gen[j]) ? '0' : '1';
            }
        }
    }

    int idx = strlen(out)-strlen(gen)+1;

    for(i=0; i<strlen(gen)-1; i++)
    {
        rem[i] = out[idx+i];
    }

}

int main()
{
    int i, j;

    char dword[MAX]; // dataword
    char augWord[MAX]; // augmented dataword
    char cword[MAX]; // codeword
    char rem[MAX]; // remainder from crc
    char gen[] = "10001000000100001";

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

    char recv[MAX];
    printf("\n\nEnter the data received : ");
    scanf("%s", recv);

    if(strlen(recv) < strlen(cword))
    {
        printf("\n Invalid input \n");
        exit(0);
    }

    crc(recv, gen, rem);

    for(i=0; i<strlen(rem); i++)
    {
        if(rem[i] == '1')
        {
            printf("\nError occured !!! Corrupted data received. \n");
            exit(0);
        }
    }
    printf("\nNo Error. Data recieved successfully.\n");
}

/*************** Output -1 *************************
CRC-16 Generator : x^16 + x^12 + x^5 + 1
Binary Form      : 10001000000100001

Enter Dataword   : 100010

Augmented dataword is   : 1000100000000000000000

Final data transmitted  : 1000100000010000100000

Enter the data received : 1000100000010000100000

No Error. Data recieved successfully.
*****************************************************/


/*************** Output -2 *************************
CRC-16 Generator : x^16 + x^12 + x^5 + 1
Binary Form      : 10001000000100001

Enter Dataword   : 1111000

Augmented dataword is   : 11110000000000000000000

Final data transmitted  : 11110001111111110011111

Enter the data received : 11110001111111111001110

Error occured !!! Corrupted data received.
*****************************************************/