#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 100

void appendChar(char str[] , char c){
     char arr[2] = {c , '\0'};
     strcat(str , arr);
}

// void printBinary(unsigned char num) {
//   for (int i = 7; i >= 0; i--) {
//     if ((num & (1 << i)) != 0)
//       printf("1");
//     else
//       printf("0");
//   }
//   printf("\n");
// }

char * getBinaryString(unsigned char num) {
  char * temp = malloc(100);
  strcpy(temp, "");

  for (int i = 7; i >= 0; i--) {
    if ((num & (1 << i)) != 0)
      appendChar(temp, '1');
    else
      appendChar(temp, '0');
  }

  return temp;
}

void xor_strings(char *a, char *b, char *result) {
    int i;
    for (i = 0; i < strlen(a); i++) {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    result[i] = '\0';
}

int main(int argc, char const *argv[])
{
    char msg[SIZE];
    strcpy(msg, "abcd");

    int len = strlen(msg);

    char msg_binary[SIZE];

    for(int i=0; i < len; i++){
        // printf("%d ", msg[i]);
        // printBinary(msg[i]);
        // printf("%s\n", getBinaryString(msg[i]));
        strcat(msg_binary, getBinaryString(msg[i]));
    }

    printf("%s\n", msg);
    printf("%s\n", msg_binary);

    char l0[SIZE], r0[SIZE];
    int len2 = strlen(msg_binary);

    for (int i = 0; i < len2/2; i++)
    {
      l0[i] = msg_binary[i];
      r0[i] =  msg_binary[len2/2 + i];
    }
    
    printf("%s\t%s\n", l0, r0);

    return 0;
}
