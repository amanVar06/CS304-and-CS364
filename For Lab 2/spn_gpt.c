#include <stdio.h>
#include <stdint.h>

#define NUM_ROUNDS 16

const uint8_t S[16] = {0x0E, 0x04, 0x0D, 0x01, 0x02, 0x0F, 0x0B, 0x08, 0x03, 0x0A, 0x06, 0x0C, 0x05, 0x09, 0x00, 0x07};
const uint8_t P[16] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};

uint8_t substitute(uint8_t block) {
    return S[block];
}

uint8_t permute(uint8_t block) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result |= ((block >> i) & 1) << (P[i] - 1);
    }
    return result;
}

int main(void) {
    uint32_t input = 0x89ABCDEF;
    uint32_t key = 0x01234567;
    uint8_t block_1 = (input >> 24) & 0xff;
    uint8_t block_2 = (input >> 16) & 0xff;
    uint8_t block_3 = (input >> 8) & 0xff;
    uint8_t block_4 = input & 0xff;

    for (int i = 0; i < NUM_ROUNDS; i++) {
        block_1 = substitute(block_1) ^ (key >> 24) & 0xff;
        block_2 = substitute(block_2) ^ (key >> 16) & 0xff;
        block_3 = substitute(block_3) ^ (key >> 8) & 0xff;
        block_4 = substitute(block_4) ^ key & 0xff;

        block_1 = permute(block_1);
        block_2 = permute(block_2);
        block_3 = permute(block_3);
        block_4 = permute(block_4);
    }

    printf("Block 1: 0x%02x\n", block_1);
    printf("Block 2: 0x%02x\n", block_2);
    printf("Block 3: 0x%02x\n", block_3);
    printf("Block 4: 0x%02x\n", block_4);

    return 0;
}
