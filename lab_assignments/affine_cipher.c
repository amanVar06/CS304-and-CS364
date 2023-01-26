#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int m = 26;

char * encryptMessage(char msg[], int a, int b)
{
    char * cipher = malloc(50);;
	strcpy(cipher, "");
	int length = strlen(msg); 

    for (int i = 0; i < length; i++)
    {
		int x = (int) msg[i] - 'A';	
		int c = (a * x + b) % m; 
		char ch = (char) (c + 'A');

        if(msg[i]!=' ') strncat(cipher, &ch, 1);
        else strncat(cipher, &msg[i], 1);   
    }

    return cipher;
}

char * decryptCipher(char cipher[], int a, int b)
{
	char * msg = malloc(50);
	strcpy(msg, "");
	int length = strlen(cipher);

    int inv = 0;   

    for (int i = 0; i < m; i++){       
        if ((a * i) % m == 1) {
            inv = i;
            break;
        }
    }

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] + 'A'; 
		int x = (inv * (c - b)) % m; 
		char ch = (char) x + 'A';

        if(cipher[i]!=' ') strncat(msg, &ch, 1);                       
        else strncat(msg, &cipher[i], 1);
    }
 
    return msg;
}

int main()
{
	char input[50]; 
	strcpy(input, "AMAN VARSHNEY");
	
    int a = 17, b= 20; //gcd(a, 26) should be 1

	char * cipherText = encryptMessage(input, a, b);
	printf("Encrypted Message is : %s\n", cipherText);

	printf("Decrypted Message is : %s\n", decryptCipher(cipherText, a, b));	

	return 0;
}

