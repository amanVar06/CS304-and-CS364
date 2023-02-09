#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int S[16] = {0x0E, 0x04, 0x0D, 0x01, 0x02, 0x0F, 0x0B, 0x08, 0x03, 0x0A, 0x06, 0x0C, 0x05, 0x09, 0x00, 0x07};
int P[16] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};

uint32_t key = 0x01234567;
uint32_t plaintext = 0x89ABCDEF;

int main(int argc, char const *argv[])
{
    //We will consider x as the plaintext (input hexadecimal) and y will be the ciphertext (output).
    // uint32_t key = 0x01234567;
    // printf("key: %X\n", key);

    // uint32_t X = 0x89ABCDEF;
    // printf("plain text: %X\n", X);

    // for (int i = 0; i < 16; i++) {
    //     printf("S[%d] = %x\n", i, S[i]);
    // }

    uint32_t input = 0x89ABCDEF;

    uint8_t block_1 = (input >> 24) & 0xff;
    uint8_t block_2 = (input >> 16) & 0xff;
    uint8_t block_3 = (input >> 8) & 0xff;
    uint8_t block_4 = input & 0xff;

    printf("Block 1: 0x%02x\n", block_1);
    printf("Block 2: 0x%02x\n", block_2);
    printf("Block 3: 0x%02x\n", block_3);
    printf("Block 4: 0x%02x\n", block_4);

    return 0;
}
