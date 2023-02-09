#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

const uint8_t sub[16] = {0x0E, 0x04, 0x0D, 0x01, 0x02, 0x0F, 0x0B, 0x08, 0x03, 0x0A, 0x06, 0x0C, 0x05, 0x09, 0x00, 0x07};
const uint8_t perm[16] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
//{0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};

uint8_t reverse_sub[16];

void create_reverse_sub_table() {
    for (int i = 0; i < 16; i++) {
        reverse_sub[sub[i]] = i;
    }
}

uint16_t permute_bits(uint16_t x)
{
    uint16_t y = 0;
    for (int i = 0; i < 16; i++)
    {
        y |= ((x >> i) & 1) << (perm[i]-1);
    }
    return y;
}

void print_binary(uint16_t n) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

uint16_t applySubstitution(uint16_t output) {

    uint8_t high = (uint8_t)((output & 0xF000) >> 12);
    uint8_t mid_high = (uint8_t)((output & 0x0F00) >> 8);
    uint8_t mid_low = (uint8_t)((output & 0x00F0) >> 4);
    uint8_t low = (uint8_t)(output & 0x000F);

    high = sub[high];
    mid_high = sub[mid_high];
    mid_low = sub[mid_low];
    low = sub[low];

    output = (uint16_t)((high << 12) | (mid_high << 8) | (mid_low << 4) | low);
    printf("Output after substitution: 0x%04X\n", output);  
    return output;  
}


uint16_t applyReverseSubstitution(uint16_t output) {

    uint8_t high = (uint8_t)((output & 0xF000) >> 12);
    uint8_t mid_high = (uint8_t)((output & 0x0F00) >> 8);
    uint8_t mid_low = (uint8_t)((output & 0x00F0) >> 4);
    uint8_t low = (uint8_t)(output & 0x000F);

    high = reverse_sub[high];
    mid_high = reverse_sub[mid_high];
    mid_low = reverse_sub[mid_low];
    low = reverse_sub[low];

    output = (uint16_t)((high << 12) | (mid_high << 8) | (mid_low << 4) | low);
    printf("Output after reverse substitution: 0x%04X\n", output);  
    return output;  
}

int main(int argc, char const *argv[])
{
    // taking plaintext as hexadecimal input (in string) 
    // then converting it into 16 bit integer with strloul
    char hex_str[5];
    uint16_t M;

    printf("Enter a hexadecimal value (4 characters (16 bits))[Use Capital Letters]: ");
    scanf("%s", hex_str);

    M = (uint16_t) strtoul(hex_str, NULL, 16);
    printf("The Plain Text(hexadecimal input): 0x%04X\n", M);

    //generating random key of 32 bits every time
    uint32_t K;

    srand(time(NULL));
    K = rand();

    printf("The Key value in hexadecimal is: 0x%08X\n", K);

    //Generating Round Keys

    uint16_t round_keys[5];

    for (int i = 0; i < 5; i++) {
        int start = (4 * (i + 1)) - 3;
        round_keys[i] = (K >> (16 - (start - 1))) & 0xFFFF;
    }

    printf("K(Secret Key) = 0x%X\n", K);
    printf("Binary representation of K: ");

    for (int i = 31; i >= 0; i--) {
        printf("%d", (K >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }

    printf("\n");
    printf("\n");

    for (int i = 0; i < 5; i++) {
        printf("K%d = 0x%X\n", i + 1, round_keys[i]);
        printf("Binary representation of K%d: ", i + 1);
        print_binary(round_keys[i]);
        printf("\n");
    }

    //Encryption

    printf("-----------------Encryption-----------------\n\n");

    printf("Plain Text: 0x%04X\n\n", M);
    // uint16_t output = round_keys[0] ^ M;
    // printf("Output after XOR with round_keys[0]: 0x%04X\n", output);
    // // print_binary(output);
    // output = applySubstitution(output);
    uint16_t output = M; //initialising output with plain text


    for (int i = 0; i < 5; i++) {
        //XOR with round keys for Encryption
        output = output ^ round_keys[i];
        printf("Output after XOR with round_keys[%d]: 0x%04X\n", i, output);

        //substitution box
        output = applySubstitution(output);

        //permutation box

        // printf("Output before permutation: 0x%04X\n", output);
        // printf("Binary representation before permutation: ");
        // print_binary(output);

        output = permute_bits(output);
        printf("Output after permutation: 0x%04X\n\n", output);
        // printf("Binary representation after permutation: ");
        // print_binary(output);
    }    

    printf("Encrypted Text: 0x%04X\n", output);
    printf("\n");
    printf("\n");

    // Decryption
    printf("-----------------Decryption------------------\n\n");

    printf("Cipher Text: 0x%04X\n\n", output);
    create_reverse_sub_table();

    for (int i = 4; i >= 0; i--) {
        //reverse permutation

        // printf("Output before reverse permutation: 0x%04X\n", output);
        // printf("Binary representation before before permutation: ");
        // print_binary(output);

        output = permute_bits(output);
        printf("Output after reverse permutation: 0x%04X\n", output);
        // printf("Binary representation after reverse permutation: ");
        // print_binary(output);

        //reverse substitution
        // printf("\n");
        output = applyReverseSubstitution(output);
        // printf("\n");

        //XOR with round keys for Decryption
        output = output ^ round_keys[i];
        printf("Output after XOR with round_keys[%d]: 0x%04X\n\n", i, output);
    }

    printf("Decrypted Text: 0x%04X\n\n", output);

    return 0;
}
