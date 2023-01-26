#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int key = 3;
const int m = 26;

char * encryptMessage(char msg[])
{
    char * cipher = malloc(100);
	strcpy(cipher, "");
	int length = strlen(msg) - 1; //ignoring null character


    for (int i = 0; i < length; i++)
    {
		int x = (int) msg[i] - 'A';	//plain text (mapping 0-25)
		int c = (x + key) % m; //cipher text
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
		int c = (int) cipher[i] + 'A'; //cipher text
		int x = ((c - key) + m) % m; //plain text
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