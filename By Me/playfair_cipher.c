// C program to implement Playfair Cipher 
//Encryption

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

void generateKeyTable(char key[], int ks, char keyT[5][5])
{
	int i, j, k, flag = 0;

	// a 26 character hashmap
	int * dictionary = (int*)calloc(26, sizeof(int));

	for (i = 0; i < ks; i++) {
		if (key[i] != 'j') 	dictionary[key[i] - 97] = 2;
	}

	dictionary['j' - 97] = 1;

	i = 0;
	j = 0;

	for (k = 0; k < ks; k++) {
		if (dictionary[key[k] - 97] == 2) {
			dictionary[key[k] - 97] -= 1; //for repeating letter in key
			keyT[i][j] = key[k];
            printf("%c ", keyT[i][j]);
			j++;
			if (j == 5) {
				i++;
				j = 0;
                printf("\n");
			}
		}
	}

	for (k = 0; k < 26; k++) {
		if (dictionary[k] == 0) {
			keyT[i][j] = (char)(k + 97);
            printf("%c ", keyT[i][j]);
			j++;
			if (j == 5) {
				i++;
				j = 0;
                printf("\n");
			}
		}
	}
}

char * prepareString(char msg[], int ps) {
    char * str = malloc(SIZE);
    strcpy(str, "");
    int count = 0;
    int i=0;

    for (i = 0; i < ps; i += 2) {
        // printf("%c %c\n", msg[i], msg[i+1]);
        if(msg[i] == msg[i+1]) {
            str[count++] = msg[i];
            str[count++] = 'x';
            i -= 1;
        }else {
            str[count++] = msg[i];
            if(msg[i+1] == '\0' || msg[i+1] == '\n') str[count++] = 'x';
            // \n because the last char in string is \n because we are taking it as an input
            else str[count++] = msg[i+1];
        }
    }

    return str;
}

// Function to search for the characters of a digraph
// in the key square and return their position
void search(char keyT[5][5], char a, char b, int arr[])
{
	int i, j;

	if (a == 'j') 	a = 'i';
	else if (b == 'j') 	b = 'i';

	for (i = 0; i < 5; i++) {

		for (j = 0; j < 5; j++) {

			if (keyT[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyT[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}


// Function for performing the encryption
void encrypt(char str[], char keyT[5][5], int ps)
{
	int i, a[4];

	for (i = 0; i < ps; i += 2) {

		search(keyT, str[i], str[i + 1], a);

		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][(a[1] + 1)%5];
			str[i + 1] = keyT[a[0]][(a[3] + 1)%5];
		}
		else if (a[1] == a[3]) {
			str[i] = keyT[(a[0] + 1)%5][a[1]];
			str[i + 1] = keyT[(a[2] + 1)%5][a[1]];
		}
		else {
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

// Function to encrypt using Playfair Cipher
char * encryptByPlayfairCipher(char msg[], char key[])
{
    char * str = prepareString(msg, strlen(msg)-1);
    printf("Final string: %s\n", str);

	char keyT[5][5];  
    int ks = strlen(key) - 1;  

    //make plain text of even length
    int len = strlen(str);
    printf("Length of the string: %d\n", len);
    printf("Length of the key: %d\n", ks);

    // int i = 0;
    // while (str[i] != '\0')
    // {
    //     printf("The Character at %d Index Position = %c \n", i, str[i]);
    //     i++;
    // }

    // i = 0;
    // while (key[i] != '\0')
    // {
    //     printf("The Character at %d Index Position = %c \n", i, key[i]);
    //     i++;
    // }

	generateKeyTable(key, ks, keyT);
	encrypt(str, keyT, len);

    return str;
}

void decrypt(char str[], char keyT[5][5], int ps)
{
	int i, a[4];
	for (i = 0; i < ps; i += 2) {
		search(keyT, str[i], str[i + 1], a);
		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][(a[1] - 1 + 5)%5];
			str[i + 1] = keyT[a[0]][(a[3] - 1 + 5)%5];
            printf("%d %d %d\n",a[0], (a[1]-1)%5, (a[3] -1)%5);
            // printf("str[i] = %c and str[i+1] = %c\n", str[i], str[i+1]);
		}
		else if (a[1] == a[3]) {
			str[i] = keyT[(a[0] - 1 + 5)%5][a[1]];
			str[i + 1] = keyT[(a[2] - 1 + 5)%5][a[1]];
		}
		else {
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}
}

char * decryptByPlayfairCipher(char msg[], char key[])
{
    char * str = malloc(SIZE);
    strcpy(str, msg);

	char keyT[5][5];

    int ks = strlen(key)-1; //key
    generateKeyTable(key, ks, keyT);

	// ciphertext
    int len = strlen(str);
    printf("Length of the string: %d\n", len);
	decrypt(str, keyT, len);
    return str;
}

int main()
{
    //assuming string always in lower case
	char msg[SIZE], key[SIZE];

	printf("Enter Key: ");
    fgets(key, sizeof(key), stdin);  // read string
    printf("Key: ");
    puts(key);    // display string

	// strcpy(key, "playfairexample");
	// printf("Key text: %s\n", key);	

	// Message to be encrypted
    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);  // read string
    printf("Message: ");
    puts(msg);    // display string


    // printf("Length of message: %d\n", (int)strlen(msg));

    // char * finalString = prepareString(msg,strlen(msg) -1);
    // printf("Prepared String: %s\n", finalString);

	// encrypt using Playfair Cipher
	char * cipherText = encryptByPlayfairCipher(msg, key);
	printf("Cipher text: %s\n", cipherText);

    //decryption
    char * plainText = decryptByPlayfairCipher(cipherText, key);
    printf("Plain text: %s\n", plainText);

	return 0;
}


