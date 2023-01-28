#include<stdio.h>
#include<string.h>

char keyword[20], plain[50], encrypted[50]={ }, new_plain[50]={ };
int ch,i,j,k,z;
char arr[5][5]={ };
char alphabets[] = "abcdefghiklmnopqrstuvwxyz";
char key_alph[50];
int l, alen;

int key(char keyword[])
{
    int len = strlen(keyword);
    for(i=0;keyword[i] != '\0'; i++)
    {
        if(keyword[i] == 'j')
            keyword[i] = 'i';
    }

    for(i=0; i<len; i++)
    {
        for(j=i+1; keyword[j] != '\0'; j++)
        {
            if(keyword[j]==keyword[i])
            {
                for(k=j; keyword[k] != '\0'; k++)
                {
                    keyword[k] = keyword[k+1];
                }
            }
        }
    }
    len = strlen(keyword);
    printf("\nEntered Keyword is: ");
    printf("%s", keyword);

    for(k=0; alphabets[k] != '\0'; k++)
    {
        for(l=0; keyword[l] != '\0'; l++)
        {
            if(keyword[l] == alphabets[k])
            {
                for(z=k; alphabets[z] != '\0'; z++)
                {
                    alphabets[z] = alphabets[z+1];
                }
            }
         }
    }
    alen = strlen(alphabets);
    printf("\nRemaining alphabets will be: ");
    printf("%s\n", alphabets);

    strcat(key_alph,keyword);
    strcat(key_alph,alphabets);

    l = 0;
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {
            arr[i][j] = key_alph[l];
            l++;
        }
    }

    printf("\nKeyMatrix will be -\n");
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {
            printf("\t%c", arr[i][j]);
        }
        printf("\t\n");
    }
    return 0;
}

int cipher(char v, char w, char arr[5][5])
{
    int r1,r2,c1,c2;
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                if(v == arr[i][j])
                {
                    r1=i;
                    c1=j;
                }

                else if(w == arr[i][j])
                {
                    r2=i;
                    c2=j;
                }
            }
        }

        if(r1==r2)
        {
            c1 = (c1 + 1) % 5;
            c2 = (c2 + 1) % 5;
            printf("%c%c ", arr[r1][c1], arr[r2][c2]);
        }

        else if(c1==c2)
        {
            r1 = (r1 + 1) % 5;
            r2 = (r2 + 1) % 5;
            printf("%c%c ", arr[r1][c1], arr[r2][c2]);
        }

        else
        {
            printf("%c%c ", arr[r1][c2], arr[r2][c1]);
        }

        return 0;
}

int decipher(char v, char w, char arr[5][5])
{
    int r1,r2,c1,c2;
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                if(v == arr[i][j])
                {
                    r1=i;
                    c1=j;
                }

                else if(w == arr[i][j])
                {
                    r2=i;
                    c2=j;
                }
            }
        }
        if(r1==r2)
        {
            if(c1==0)
            {
                c1=4;
                c2 = (c2 - 1) % 5;
            }
            else if(c2==0)
            {
                c2=4;
                c1 = (c1 - 1) % 5;
            }
            else{
            c1 = (c1 - 1) % 5;
            c2 = (c2 - 1) % 5;
            }

            if(arr[r2][c2] == 'x')
                arr[r2][c2] = '\0';

            printf("%c%c ", arr[r1][c1], arr[r2][c2]);
        }
        else if(c1 == c2)
        {
            if(r1==0)
            {
                r1=4;
                r2 = (r2 - 1) % 5;
            }
            else if(r2==0)
            {
                r2=4;
                r1 = (r1 - 1) % 5;
            }
            else{
            r1 = (r1 - 1) % 5;
            r2 = (r2 - 1) % 5;
            }

            if(arr[r2][c2] == 'x')
                arr[r2][c2] = '\0';

            printf("%c%c ", arr[r1][c1], arr[r2][c2]);
        }
        else
        {
            if(arr[r2][c1] == 'x')
                arr[r2][c1] = '\0';

            printf("%c%c ", arr[r1][c2], arr[r2][c1]);
        }
    return 0;
}


void main()
{
    printf("Playfair Cipher\n");
    do
    {
        printf("\n1. Encryption\t2. Decryption\t3. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch)
        {
        case 1:
            printf("Enter the key: ");
            scanf("%s",keyword);

            key(keyword);

            printf("\n\nEnter the plain text: ");
            scanf("%s",plain);
            i=0;
            j=0;
            k=0;

            int plen = strlen(plain);
            for(i=0; i<plen; i++)
            {
                if(plain[i] == plain[i+1])
                {
                    for(j=plen; j>i; j--)
                    {
                        plain[j+1] = plain[j];
                    }
                    plain[j+1] = 'x';
                }
            }

            plen = strlen(plain);
            if(plen%2 != 0)
            {
                strcat(plain,"x");
            }

            plen = strlen(plain);
            /*
            for(k=0; new_plain[k] != plain[plen];)
            {
                for(i=0; i<plen; i++)
                {
                    if(i%2 == 0 && i != 0)
                    {
                        new_plain[k] = ' ';
                        k++;
                        new_plain[k] = plain[i];
                        k++;
                    }
                    else{
                        new_plain[k] = plain[i];
                        k++;
                    }
                }
            }*/
            strcpy(new_plain,plain);

            printf("\nNew Plain text will be: ");
            puts(new_plain);
            printf("\n");

            k=0;
            printf("Encrypted text will be: ");
            for(k = 0; k < plen;k++)
            {
                if (new_plain[k] == 'j')
                    new_plain[k] = 'i';

                if(new_plain[k+1] == 'j')
                    new_plain[k] = 'i';

                cipher(new_plain[k], new_plain[k + 1], arr);
                k++;
            }
            break;

        case 2:
            printf("Enter the key: ");
            scanf("%s",keyword);

            key(keyword);

            printf("Enter cipher text: ");
            scanf("%s", &encrypted);
            int elen = strlen(encrypted);
            printf("Decrypted text will be: ");
            l=0;
            for(l = 0; l < elen;l++)
            {
                if (encrypted[l] == 'j')
                    encrypted[l] = 'i';

                if(encrypted[l+1] == 'j')
                    encrypted[l] = 'i';

                decipher(encrypted[l], encrypted[l + 1], arr);
                l++;
            }

            break;
        }
    }while(ch != 3);
}