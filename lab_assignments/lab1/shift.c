#include<stdio.h>
#include<string.h>
#include <stdlib.h>

const char k = 'g';
const int key = k - 'a';
const int m = 26;

char * encryptMessage(char msg[])
{
    char * cipher = malloc(100);
	strcpy(cipher, "");
	int length = strlen(msg); 

    for (int i = 0; i < length; i++)
    {
		int x = (int) msg[i] - 'A';	
		int c = (x + key) % m;
		char ch = (char) (c + 'A');

        strncat(cipher, &ch, 1);
           
    }

    return cipher;
}

char * decryptCipher(char cipher[])
{
	char * msg = malloc(100);
	strcpy(msg, "");
	int length = strlen(cipher);

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] + 'A';
		int x = ((c - key) + m) % m; 
		char ch = (char) x + 'A';

        strncat(msg, &ch, 1);                       
        
    }
 
    return msg;
}

int main(int argc, char const *argv[])
{
    char input[50];
    strcpy(input, "ENCRYPT");

    char * ans = encryptMessage(input);
    printf("Encrypted Text: %s\n", ans);

    printf("Decrypted Text: %s\n", decryptCipher(ans));

    return 0;
}