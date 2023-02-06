#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define SIZE 100

void divideIntoHalves(char msg[], char left[], char right[], int len) {
    
    for(int i=0; i<len/2; i++) {
        left[i] = (msg[i]);
        // printf("%d\n", left[i]);
    }

    for(int i=len/2; i<len; i++) {
        right[i] = (msg[i]);
        // printf("%d\n", right[i]);
    }
}



int main(int argc, char const *argv[])
{
    //assuming string always in lower case
	char msg[SIZE], key[SIZE];

    int left[SIZE/2]; //L0
    int right[SIZE/2]; //R0

    strcpy(msg, "encrypt");
	

	// Message to be encrypted
    // printf("\nEnter message: ");
    // fgets(msg, sizeof(msg), stdin);  // read string
    // printf("Message: ");
    // puts(msg);    // display string

    divideIntoHalves(msg, left, right, strlen(msg)-1);


	// encrypt 
	// char * cipherText = encryptByPlayfairCipher(msg, key);
	// printf("Cipher text: %s\n", cipherText);

    //decryption
    // char * plainText = decryptByPlayfairCipher(cipherText, key);
    // printf("Plain text: %s\n", plainText);
    return 0;
}
