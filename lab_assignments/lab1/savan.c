#include<stdio.h>
#include<string.h>
int check(char table[5][5], char k) {
    int i, j;
    for (i = 0; i < 5; ++i)
        for (j = 0; j < 5; ++j) {
            if (table[i][j] == k)
                return 0;
        }
    return 1;
}


void encryptByAffine(char msg[], int a, int b)
{
	int length = strlen(msg); 
    int m = 26;

    for (int i = 0; i < length; i++)
    {
		msg[i] = (char) (((a * ((int) msg[i] - 97) + b) % m) + 97); 
    }
}

void decryptCipherByAffine(char cipher[], int a, int b)
{
	int length = strlen(cipher);
    int a_inv = 0;   
    int m = 26;

    for (int i = 0; i < m; i++){       
        if ((a * i) % m == 1) a_inv = i;
    }

    // printf("%d\n", a_inv);

    for (int i = 0; i < length; i++)
    {
		char ch = (char) ((a_inv * (cipher[i] - 97 - b + m)) % m) + 97;
        cipher[i] = ch;                     
    }
}

void encryptByShift(char msg[], int key)
{
	int length = strlen(msg); 
    int m = 26;

    for (int i = 0; i < length; i++)
    {
        msg[i] = (char) ((((msg[i] - 97) + key) % m) + 97);
           
    }
}

void decryptCipherByShift(char cipher[], int key)
{
	int length = strlen(cipher);
    int m = 26;

    for (int i = 0; i < length; i++)
    {
		cipher[i] = (char) (((cipher[i] - 97 - key) + m) % m) + 97;                   
    }
}



void main() {
    int i, j; 
    int KeyLength;
    char table[5][5];

    for (i = 0; i < 5; ++i)
        for (j = 0; j < 5; ++j)
            table[i][j] = '0';
 
    printf("Enter Key Length: ");
    scanf("%d", &KeyLength);
 
    char key[50];
 
    printf("Enter Key: ");
    scanf("%s", key);
    // for (i = -1; i < KeyLength; ++i) {
    //     scanf("%c", &key[i]);
    //     if (key[i] == 'j')
    //         key[i] = 'i';
    // }
    // int len1 = strlen(key);

    printf("%s\n", key);
 
    int flag;
    int count = 0;
 
    // inserting the key into the table
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            flag = 0;
            while (flag != 1) {
                if (count > KeyLength)
                    goto l1;
 
                flag = check(table, key[count]);
                ++count;
            }// end of while
            table[i][j] = key[(count - 1)];
        }// end of inner for
    }// end of outer for
 
 
    l1: printf("\n");
 
    int val = 97;
    //inserting other alphabets
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if (table[i][j] >= 97 && table[i][j] <= 123) {
            } else {
                flag = 0;
                while (flag != 1) {
                    if ('j' == (char) val)
                        ++val;
                    flag = check(table, (char) val);
                    ++val;
                }// end of while
                table[i][j] = (char) (val - 1);
            }//end of else
        }// end of inner for
    }// end of outer for
 
    printf("Table:\n");
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
 
    int l = 0;
    printf("\nEnter Length of Plaintext (w/o spaces): ");
    scanf("%d", &l);
 
    printf("\nEnter Plaintext : ");
    // char p[l];
    // for (i = -1; i < l; ++i) {
    //     scanf("%c", &p[i]);
    // }

    char p[50];
    scanf("%s", p);
 
    for (i = -1; i < l; ++i) {
        if (p[i] == 'j')
            p[i] = 'i';
    }
 
    printf("\n Replaced text:");
    for (i = -1; i < l; ++i)
        printf("%c ", p[i]);
 
    count = 0;
    for (i = -1; i < l; ++i) {
        if (p[i] == p[i + 1])
            count = count + 1;
    }
 
    printf("\nThe cipher has to enter %d bogus char.It is either 'x' or 'z'\n",
            count);
 
    int length = 0;
    if ((l + count) % 2 != 0)
        length = (l + count + 1);
    else
        length = (l + count);
 
    printf("\nValue of length is %d.\n", length);
    char p1[length];
 
    //inserting bogus characters.
    char temp1;
    int count1 = 0;
    for (i = -1; i < l; ++i) {
        p1[count1] = p[i];
        if (p[i] == p[i + 1]) {
            count1 = count1 + 1;
            if (p[i] == 'x')
                p1[count1] = 'z';
            else
                p1[count1] = 'x';
        }
        count1 = count1 + 1;
    }
 
    //checking for length
 
    char bogus;
    if ((l + count) % 2 != 0) {
        if (p1[length - 1] == 'x')
            p1[length] = 'z';
        else
            p1[length] = 'x';
    }
 
    printf("The final text is:");
    for (i = 0; i <= length; ++i)
        printf("%c ", p1[i]);
 
    char cipher_text[length];
    int r1, r2, c1, c2;
    int k1;
 
    for (k1 = 1; k1 <= length; ++k1) {
        for (i = 0; i < 5; ++i) {
            for (j = 0; j < 5; ++j) {
                if (table[i][j] == p1[k1]) {
                    r1 = i;
                    c1 = j;
                } else if (table[i][j] == p1[k1 + 1]) {
                    r2 = i;
                    c2 = j;
                }
            }//end of for with j
        }//end of for with i
 
        if (r1 == r2) {
            cipher_text[k1] = table[r1][(c1 + 1) % 5];
            cipher_text[k1 + 1] = table[r1][(c2 + 1) % 5];
        }
 
        else if (c1 == c2) {
            cipher_text[k1] = table[(r1 + 1) % 5][c1];
            cipher_text[k1 + 1] = table[(r2 + 1) % 5][c1];
        } else {
            cipher_text[k1] = table[r1][c2];
            cipher_text[k1 + 1] = table[r2][c1];
        }
 
        k1 = k1 + 1;
    }//end of for with k1
 
    printf("\n\nThe Cipher text C1 is:\n ");
    for (i = 1; i <= length; ++i)
        printf("%c ", cipher_text[i]);

    encryptByAffine(cipher_text, 11, 15);
    printf("\n\nThe Cipher text C2 is:\n ");
    for (i = 1; i <= length; ++i)
        printf("%c ", cipher_text[i]);

    encryptByShift(cipher_text, 10);
    printf("\n\nThe Cipher text C3 is:\n ");
    for (i = 1; i <= length; ++i)
        printf("%c ", cipher_text[i]);

    decryptCipherByShift(cipher_text, 10);
    printf("\n\nThe decrypted text of C3 is:\n ");
    for (i = 1; i <= length; ++i)
        printf("%c ", cipher_text[i]); 

    decryptCipherByAffine(cipher_text, 11, 15);
    printf("\n\nThe decrypted text of C2 is:\n ");
    for (i = 1; i <= length; ++i)
        printf("%c ", cipher_text[i]);
 
}