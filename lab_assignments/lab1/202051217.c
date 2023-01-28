#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

const int a = 11; //FOR AFFINE
const int b = 15; //FOR AFFINE
const int m = 26;
const int k3 = 10; //FOR SHIFT

void generateKeyTable(char * key, int keysize, char keyT[5][5])
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

	free(dictionary);
}

char * prepareStringForEncryption(char * msg, int len) {
    char * str = malloc(SIZE);
    strcpy(str, "");
    int count = 0;
    int i=0;

    for(int j=0; j<len; j++) {
        if(msg[j] == 'J') msg[j] = 'I';
    }

    for (i = 0; i < len; i += 2) {
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

	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < 5; j++) {

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
void encryptByPlayfair(char * str, char keyT[5][5], int len)
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
void decryptByPlayfair(char * str, char keyT[5][5], int len)
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

// Extended Euclidean Algorithm
int gcdExtended(int a, int b, int* x, int* y)
{
	// Base Case
	if (a == 0) {
		*x = 0, *y = 1;
		return b;
	}

	int x1, y1; // To store results of recursive call
	int gcd = gcdExtended(b % a, a, &x1, &y1);

	// Update x and y using results of recursive
	// call
	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

// Function to find modulo inverse of a
int modInverse(int A, int M)
{
	int x, y, res = 1;
	int g = gcdExtended(A, M, &x, &y);
	if (g != 1){
		printf("Inverse doesn't exist");
	}
	else {
		// m is added to handle negative x
		res = (x % M + M) % M;
		// printf("\nModular multiplicative inverse of %d is %d\n", A, res);
	}

	return res;
}

void encryptByAffine(char * msg)
{
	int length = strlen(msg);
	// E ( x ) = ( a x + b ) mod m 

    for (int i = 0; i < length; i++)
    {
		int x = (int) msg[i] - 'A';	//plain text (mapping 0-25)
		int c = (a * x + b) % m; //cipher text
		char ch = (char) (c + 'A');

        msg[i] = ch;          
    }

}

void decryptCipherByAffine(char * cipher)
{
	int length = strlen(cipher);

    int a_inv = modInverse(a, m); 
	//D ( x ) = a^-1 ( c - b ) mod m
	//1 = a a^-1 mod m 

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] - 'A'; //cipher text
		int x = (a_inv * (c - b + m)) % m; //plain text
		char ch = (char) x + 'A';
 
        cipher[i] = ch;                      
    }
}


void encryptByShift(char * msg)
{

	int length = strlen(msg); 

    for (int i = 0; i < length; i++)
    {
		int x = (int) msg[i] - 'A';	
		int c = (x + k3) % m;
		char ch = (char) (c + 'A');

        msg[i] = ch;
           
    }
}

void decryptCipherByShift(char * cipher)
{
	int length = strlen(cipher);

    for (int i = 0; i < length; i++)
    {
		int c = (int) cipher[i] - 'A';
		int x = ((c - k3) + m) % m; 
		char ch = (char) x + 'A';

        cipher[i] = ch;                      
        
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
	encryptByPlayfair(str, keyTable, len);
	printf("\nCipher text C1 (After Encryption by Playfair): %s\n", str);

    encryptByAffine(str);
    printf("\nCipher text C2(Using Affine): %s\n", str);

    encryptByShift(str);
    printf("\nCipher text C3(Using Shift): %s\n", str);

    //decryption
    decryptCipherByShift(str);
    printf("\nDecryption by Shift: %s\n", str);

    decryptCipherByAffine(str);
    printf("\nDecryption by Affine: %s\n", str);

    decryptByPlayfair(str, keyTable, len);
    printf("\nDelta (After Final Decryption by Playfair): %s\n\n", str);

	return 0;
}


