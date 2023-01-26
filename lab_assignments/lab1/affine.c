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
		int x = (int) msg[i] - 'a';	//plain text (mapping 0-25)
		int c = (a * x + b) % m; //cipher text
		char ch = (char) (c + 'a');

       strncat(cipher, &ch, 1);

    }

    return cipher;
}

char * decryptCipher(char cipher[])
{
	char * msg = malloc(100);
	strcpy(msg, "");
	int length = strlen(cipher);

    int a_inv = 0;   

    for (int i = 0; i < m; i++){       
        if ((a * i) % m == 1) a_inv = i;
    }

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] + 'a'; //cipher text
        printf("%d\n", c);
		int x = (a_inv * (c - b)) % m; //plain text
        printf("%d\n", x);
		char ch = (char) x + 'a';
        strncat(msg, &ch, 1);                       

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

