#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30
const int a = 17;
const int b = 20;
const int m = 26;

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

// void printTable(char keyT[5][5]) {
// 	for(int i=0; i<5; i++) {
// 		for(int j=0; j<5; j++) {
// 			printf("%c ", keyT[i][j]);
// 		}
// 		printf("\n");
// 	}
// }

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

char * encryptByPlayfairCipher(char msg[], char key[])
{
    char * str = prepareStringForEncryption(msg, strlen(msg)-1);
    printf("Delta (String before Encryption): %s\n", str);

	char keyT[5][5];  
    int ks = strlen(key) - 1;  

    //make plain text of even length
    int len = strlen(str);
    printf("\nLength of Delta: %d\n", len);
    printf("Length of the key: %d\n", ks);

	printf("\n------Key Table:----------- \n");
	generateKeyTable(key, ks, keyT);
	printf("\n");
	
	encrypt(str, keyT, len);

    return str;
}

//decrypt by playfair cipher
void decrypt(char str[], char keyT[5][5], int ps)
{
	int i, a[4];
	for (i = 0; i < ps; i += 2) {
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

char * decryptByPlayfairCipher(char msg[], char key[])
{
    char * str = malloc(SIZE);
    strcpy(str, msg);

	char keyT[5][5];

    int ks = strlen(key)-1; //key
	printf("\n------Key Table:----------- \n");
    generateKeyTable(key, ks, keyT);
	printf("\n");

	// ciphertext
    int len = strlen(str);
	decrypt(str, keyT, len);
    return str;
}

char * encryptByAffine(char msg[])
{
    char * cipher = malloc(SIZE);
	strcpy(cipher, "");
	int length = strlen(msg); //ignoring null character

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

char * decryptCipherByAffine(char cipher[])
{
	char * msg = malloc(SIZE);
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

        strncat(msg, &ch, 1);                       
    }
 
    return msg;
}

char * encryptByShift(char msg[], int k3)
{
    char * cipher = malloc(SIZE);
	strcpy(cipher, "");
	int length = strlen(msg); 

    for (int i = 0; i < length; i++)
    {
		int x = (int) msg[i] - 'A';	
		int c = (x + k3) % m;
		char ch = (char) (c + 'A');

        strncat(cipher, &ch, 1);
           
    }

    return cipher;
}

char * decryptCipherByShift(char cipher[], int k3)
{
	char * msg = malloc(SIZE);
	strcpy(msg, "");
	int length = strlen(cipher);

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] + 'A';
		int x = ((c - k3) + m) % m; 
		char ch = (char) x + 'A';

        strncat(msg, &ch, 1);                       
        
    }
 
    return msg;
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

	//Key for playfair cipher
	printf("Enter Key for Playfair Cipher (IN UPPER CASE): ");
    fgets(key, sizeof(key), stdin);  // read string
    printf("Key: ");
    puts(key);    // display string	

    //encryption
	char * cipherTextPlayfair = encryptByPlayfairCipher(msg, key);
	printf("Cipher text I(Using Playfair): %s\n", cipherTextPlayfair);

    char * cipherTextAffine = encryptByAffine(cipherTextPlayfair);
    printf("Cipher text II(Using Affine): %s\n", cipherTextAffine);

    char * cipherTextShift = encryptByShift(cipherTextAffine, 10);
    printf("Cipher text III(Using Shift): %s\n", cipherTextShift);

    char * decryptTextShift = decryptCipherByShift(cipherTextShift, 10);
    printf("Decrypt Shift III: %s\n", decryptTextShift);

    char * decryptTextAffine = decryptCipherByAffine(decryptTextShift);
    printf("Decrypt Affine II: %s\n", decryptTextAffine);


    //decryption
    char * plainText = decryptByPlayfairCipher(cipherTextPlayfair, key);
    printf("Plain text (Decrypt Playfair): %s\n", plainText);

	return 0;
}


