#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

// Function to encrypt using the Playfair Cipher
void PlayfairCrypt(char str[], char keystr[])
{
    char keyT[5][5], ks, ps;

    // Key
    ks = strlen(keystr);
    // Plaintext
    ps = strlen(str);

    // Function to convert the string to uppercase
    // Can also use the library function toUpper here, but a function was written for better understanding of ascii values.
    void toUpperCase(char encrypt[], int ps)
    {
        int i;
        for (i = 0; i < ps; i++) {
            if (encrypt[i] > 96 && encrypt[i] < 123)
                encrypt[i] -= 32;
        }
    }

    // Function to remove all spaces in a string
    int removeSpaces(char* plain, int ps)
    {
        int i, count = 0;
        for (i = 0; i < ps; i++)
            if (plain[i] != ' ')
                plain[count++] = plain[i];
        plain[count] = '\0';
        return count;
    }

    // Function to generate the 5x5 key square
    void generateKeyTable(char keystr[], int ks, char keyT[5][5])
    {
        int i, j, k, flag = 0, *dicty;

        // a 26 character hashmap to store count of the alphabet
        dicty = (int*)calloc(26, sizeof(int));
        for (i = 0; i < ks; i++) {
            if (keystr[i] != 'j')
                dicty[keystr[i] - 97] = 2;
        }

        dicty['j' - 97] = 1;

        i = 0;
        j = 0;

        for (k = 0; k < ks; k++) {
            if (dicty[keystr[k] - 97] == 2) {
                dicty[keystr[k] - 97] -= 1;
                keyT[i][j] = keystr[k];
                j++;
                if (j == 5) {
                    i++;
                    j = 0;
                }
            }
        }

        for (k = 0; k < 26; k++) {
            if (dicty[k] == 0) {
                keyT[i][j] = (char)(k + 97);
                j++;
                if (j == 5) {
                    i++;
                    j = 0;
                }
            }
        }
    }
    
    // Function to make the plain text length even, and make pairs unidentical.
    int prepare(char str[], int ptrs)
    {
        int i, j, subs_s = ptrs;
        for (i = 0; i < subs_s; i += 2) {
            if(str[i]==str[i+1]){
                for(j=subs_s; j>i+1; j--){
                   str[j]=str[j-1];
                }
                str[i+1]='x';
                subs_s+=1;
            }
        }
        str[subs_s]='\0';

        if (subs_s % 2 != 0) {
            str[subs_s++] = 'z';
            str[subs_s] = '\0';
        }
        return subs_s;
    }

    // Function to search for the characters of a digraph in the key square and return their position
    void search(char keyT[5][5], char a, char b, int arr[])
    {
        int i, j;

        if (a == 'j')
            a = 'i';
        else if (b == 'j')
            b = 'i';

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

        for(i=0; i<ps; i+=2){

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
    printf("playcipher matrix ");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%c", keyT[i][j]);
            
        }
        printf("\n");
    }
     printf("\n");

    ks = removeSpaces(keystr, ks);
    ps = removeSpaces(str, ps);
    ps = prepare(str, ps);
    generateKeyTable(keystr, ks, keyT);
    encrypt(str, keyT, ps);
    toUpperCase(str, ps);
    //cipher text - printed in upper case letters
    printf("play fair Cipher text: %s\n", str);
}

void Affinecipherencry(char str[],int alpha,int beta){
   int i,numstr[100],numcipher[100];
    //Storing string in terms of ascii and to restore spaces I used -20
 for(i=0;i<strlen(str);i++)
 {
  if(str[i]!=' ')
  numstr[i]=str[i]-'A';
  else
  numstr[i]=-20;
 }
 //Ciphering Process
    //If numcipher is more than 25 .We need to convert and ensure that lie in between 0 and 25.(indicating Alphabets)
    //A-0,B-1,C-2,.....Y-24,Z-25
    printf("Affine Cipher text is\n");   
    for(i=0;i<strlen(str);i++)
    {
     if(numstr[i]!=-20)
     {
     numcipher[i]=((alpha*numstr[i])+beta)%26;
          printf("%c",(numcipher[i]+'A'));         
     }
     else
     {
          printf(" ");      
     }
    }
printf("\n");
 
}

void shiftciphercrypt(char str[],int key){
    int  encrypted[100];
    for(int i=0;i<strlen(str);i++){
        encrypted[i] = ((str[i]-'a') + key)%26 + 'a';
    }
    printf("The encrypted string is : %ls\n",encrypted);
}

void shiftcipherdecrypt(char str[],int key){
    int decrypted[100];
    for(int i=0;i<10;i++){
        decrypted[i] = ((str[i]-'a') - key + 26)%26 + 'a';
    }
    printf("The decrypted string is : %ls\n",decrypted);
    
}

void Affinecipherdencry(char str[],int alpha,int beta){
    
    int GetMultiplicativeInverse(int alpha)
{
    int i,MI;
 for(i=1;i<=alpha;i++)
 {
  MI=((i*26)+1);
  if(MI%alpha==0)
  {
   break;
  }
 }
 MI=MI/alpha;
 return(MI);

    
    // int GetMultiplicativeInverse(int);
    int numstr[100],numcipher[100],alphaInverse;
    
    for(int i=0;i<strlen(str);i++)
 {
  if(str[i]!=' ')
  numstr[i]=str[i]-'A';
  else
  numstr[i]=-20;
 }
 //For Decryption we need to find multiplicative inverse of  Alpha
 alphaInverse=GetMultiplicativeInverse(alpha);
 printf("MI=%d\n",alphaInverse);
     //Deciphering Process
    //If numcipher is more than 25 .We need to convert and ensure that lie in between 0 and 25.(indicating Alphabets)
   //A-0,B-1,C-2,.....Y-24,Z-25
    printf("Affine Cipher text is\n");   
    for(i=0;i<strlen(str);i++)
    {
     if(numstr[i]!=-20)
     {
     numcipher[i]=(alphaInverse*(numstr[i]-beta))%26;
     if(numcipher[i]<0)
     {
      numcipher[i]=numcipher[i]+26;//To avoid negative numbers
     }
          printf("%c",(numcipher[i]+'A'));         
     }
     else
     {
          printf(" ");      
     }
    }
printf("\n");
}
 
}


// Convert all the characters of a string to lowercase
	// Can also use the library function toLower here, but a function was written for better understanding of ascii values.
	void toLowerCase(char plain[], int ps)
	{
		int i;
		for (i = 0; i < ps; i++) {
			if (plain[i] > 64 && plain[i] < 91)
				plain[i] += 32;
		}
	}

    void generateKeyTable(char keystr[], int ks,
						char keyT[5][5])
	{
		int i, j, k, flag = 0, *dicty;

		// a 26 character hashmap to store count of the alphabet
		dicty = (int*)calloc(26, sizeof(int));

		for (i = 0; i < ks; i++) {
			if (keystr[i] != 'j')
				dicty[keystr[i] - 97] = 2;
		}
		dicty['j' - 97] = 1;

		i = 0;
		j = 0;
		for (k = 0; k < ks; k++) {
			if (dicty[keystr[k] - 97] == 2) {
				dicty[keystr[k] - 97] -= 1;
				keyT[i][j] = keystr[k];
				j++;
				if (j == 5) {
					i++;
					j = 0;
				}
			}
		}
		for (k = 0; k < 26; k++) {
			if (dicty[k] == 0) {
				keyT[i][j] = (char)(k + 97);
				j++;
				if (j == 5) {
					i++;
					j = 0;
				}
			}
		}
	}


    void search(char keyT[5][5], char a, char b, int arr[])
	{
		int i, j;

		if (a == 'j')
			a = 'i';
		else if (b == 'j')
			b = 'i';

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

    void decrypt(char str[], char keyT[5][5], int ps)
	{
		int i, a[4];
		for (i = 0; i < ps; i += 2) {
			search(keyT, str[i], str[i + 1], a);
			if (a[0] == a[2]) {
			    if(a[1]==0){
			        str[i] = keyT[a[0]][4];
			        str[i + 1] = keyT[a[0]][(a[3] - 1)%5];
			    }
			    else if(a[3]==0){
			        str[i] = keyT[a[0]][(a[1] - 1)%5];
			        str[i + 1] = keyT[a[0]][4];
			    }
			    else{
			        str[i] = keyT[a[0]][(a[1] - 1)%5];
			        str[i + 1] = keyT[a[0]][(a[3] - 1)%5];
			    }

			}
			else if (a[1] == a[3]) {
			    if(a[0]==0){
			        str[i] = keyT[4][a[1]];
			        str[i + 1] = keyT[(a[2] - 1)%5][a[1]];
			    }
			    else if(a[2]==0){
			        str[i] = keyT[(a[0] - 1)%5][a[1]];
			        str[i + 1] = keyT[4][a[1]];
			    }
			    else{
			        str[i] = keyT[(a[0] - 1)%5][a[1]];
			        str[i + 1] = keyT[(a[2] - 1)%5][a[1]];
			    }
			}
			else {
				str[i] = keyT[a[0]][a[3]];
				str[i + 1] = keyT[a[2]][a[1]];
			}
		}
	}


    int removeSpaces(char* plain, int ps)
    {
        int i, count = 0;
        for (i = 0; i < ps; i++)
            if (plain[i] != ' ')
                plain[count++] = plain[i];
        plain[count] = '\0';
        return count;
    }



void PlayfairDeCrypt(char str[], char keystr[])
{
	char ps, ks, keyT[5][5];

	// Key
	// ks = strlen(keystr);
	// ciphertext
	// ps = strlen(str);
	
	ks = removeSpaces(keystr, ks);
	toLowerCase(str, ps);
	ps = removeSpaces(str, ps);
	generateKeyTable(keystr, ks, keyT);
	decrypt(str, keyT, ps);

	//plain text printed in lower case letters
	printf("Plain text: %s\n", str);
}



// Driver code
int main()
{
    char str[SIZE], keystr[SIZE];

    //Key used - to be entered in lower case letters
    printf("Enter the key for playcipher: ");
    scanf("%[^\n]s", keystr);
    printf("Key text: %s\n", keystr);

    printf("Enter the plaintext: ");
    scanf("\n");
    scanf("%[^\n]s", str);
    printf("Plain text: %s\n", str);

    //Calling the PlayfairCrypt function
    PlayfairCrypt(str, keystr);
    
    //calling affine cipher encrypt function
    Affinecipherencry(str,11,15);
    
    // calling shift cipher encryption
    shiftciphercrypt(str,20);  // considering key for shift cipher to  be 15
    
    //calling shiftcipher decryption
    shiftcipherdecrypt(str,20);
    
    //calling affine cipher decypyt
    Affinecipherdencry(str,11,15);
    
    //calling playfairdecrypt function
    PlayfairDeCrypt(str,keystr);


    return 0;
}