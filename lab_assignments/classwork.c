#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    char plain[10];
    char encrypted[10];
    char decrypted[10];

    int shift = 3;
    strcpy(plain, "amanvarsh");
    strcpy(encrypted, "");
    strcpy(decrypted, "");

    for(int i=0; i<10; i++) {
        encrypted[i] = ((plain[i] - 'a') + shift)%26 + 'a';
        decrypted[i] = ((encrypted[i] - 'a') -shift + 26)%26 + 'a';
    }

    printf("%s\n", encrypted);
    printf("%s\n", decrypted);
}