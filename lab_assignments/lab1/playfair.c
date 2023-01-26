#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

void generateKeyTable(char key[], int keysize, char keyT[5][5])
{
	int i, j, k;

	// a 26 character hashmap
	//allocate 26 memory locations and then initialize it to zero
	int * dictionary = (int*)calloc(26, sizeof(int));

	for (i = 0; i < keysize; i++) {
		if (key[i] != 'J') 	dictionary[key[i] - 65] = 2;
	}
	
	dictionary['J' - 65] = 1;

	i = 0;
	j = 0;

	for (k = 0; k < keysize; k++) {
		if (dictionary[key[k] - 65] == 2) {
			dictionary[key[k] - 65] -= 1; //for repeating letter in key
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
			keyT[i][j] = (char)(k + 65);
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

char * prepareStringForEncryption(char msg[], int ps) {
    char * str = malloc(SIZE);
    strcpy(str, "");
    int count = 0;
    int i=0;

    for (i = 0; i < ps; i += 2) {
        if(msg[i] == msg[i+1]) {
            str[count++] = msg[i];
            str[count++] = 'X';
            i -= 1;
        }else {
            str[count++] = msg[i];
            if(msg[i+1] == '\0' || msg[i+1] == '\n') str[count++] = 'X';
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

	if (a == 'J') 	a = 'I';
	else if (b == 'J') 	b = 'I';

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

// Function for performing the encryption in playfair cipher
void encrypt(char str[], char keyT[5][5], int len)
{
	int i, a[4];

	for (i = 0; i < len; i += 2) {

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


//decrypt by playfair cipher
void decrypt(char str[], char keyT[5][5], int len)
{
	int i, a[4];
	for (i = 0; i < len; i += 2) {
		search(keyT, str[i], str[i + 1], a);
		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][(a[1] - 1 + 5)%5];
			str[i + 1] = keyT[a[0]][(a[3] - 1 + 5)%5];
            
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

int main()
{
    //assuming string always in Upper Case
	char msg[SIZE], key[SIZE];

	// Message to be encrypted
    printf("\nEnter the plain Text (IN UPPER CASE WITHOUT SPACES): ");
    fgets(msg, sizeof(msg), stdin);  // read string
    printf("Message: ");
    puts(msg);    // display string	

    char * str = prepareStringForEncryption(msg, strlen(msg)-1);
    printf("Delta (String before Encryption): %s\n", str);

    //Key for playfair cipher
	printf("\nEnter Key for Playfair Cipher (IN UPPER CASE): ");
    fgets(key, sizeof(key), stdin);  // read string
    printf("Key: ");
    puts(key);    // display string	

    char keyTable[5][5];  
    int keysize = strlen(key) - 1;  

    int len = strlen(str);

    printf("Length of Delta: %d\n", len);
    printf("Length of the key: %d\n", keysize);

	printf("\n-----------Key Table----------- \n");
	generateKeyTable(key, keysize, keyTable);
    printf("\n");

    //encryption
	encrypt(str, keyTable, len);
	printf("Cipher text (After Encryption): %s\n", str);

    //decryption
    decrypt(str, keyTable, len);
    printf("Plain text (After Decryption): %s\n\n", str);

	return 0;
}


