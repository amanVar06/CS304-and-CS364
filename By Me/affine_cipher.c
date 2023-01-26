#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Key values of a and b
const int a = 17;
const int b = 20;
const int m = 26;

char * encryptMessage(char msg[])
{
    char * cipher = malloc(100);;
	strcpy(cipher, "");
	int length = strlen(msg) - 1; //ignoring null character

	// E ( x ) = ( a x + b ) mod m 

    for (int i = 0; i < length; i++)
    {
		int x = (int) msg[i] - 'A';	//plain text (mapping 0-25)
		int c = (a * x + b) % m; //cipher text
		char ch = (char) (c + 'A');

        if(msg[i]!=' ') strncat(cipher, &ch, 1);
        else strncat(cipher, &msg[i], 1);   
    }

    return cipher;
}

char * decryptCipher(char cipher[])
{
	char * msg = malloc(100);
	strcpy(msg, "");
	int length = strlen(cipher);

    int a_inv = 0;   

	//D ( x ) = a^-1 ( c - b ) mod m
	//1 = a a^-1 mod m 

    for (int i = 0; i < m; i++){       
        if ((a * i) % m == 1) a_inv = i;
    }

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] + 'A'; //cipher text
		int x = (a_inv * (c - b)) % m; //plain text
		char ch = (char) x + 'A';

        if(cipher[i]!=' ') strncat(msg, &ch, 1);                       
        else strncat(msg, &cipher[i], 1);
    }
 
    return msg;
}

int main(void)
{
	char msg[100]; 
	printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);  // read string
    printf("Message: ");
    puts(msg);    // display string
	

	char * cipherText = encryptMessage(msg);
	printf("Encrypted Message is : %s\n", cipherText);

	printf("Decrypted Message is : %s\n", decryptCipher(cipherText));	

	return 0;
}

