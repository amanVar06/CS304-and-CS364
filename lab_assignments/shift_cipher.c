#include<stdio.h>
#include<string.h>
#include <stdlib.h>

const char k = 'G';
const int key = k - 'A';
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

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] + 'A';
		int x = ((c - key) + m) % m; 
		char ch = (char) x + 'A';

        if(cipher[i]!=' ') strncat(msg, &ch, 1);                       
        else strncat(msg, &cipher[i], 1);
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
