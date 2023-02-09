#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
 

 int PC1[] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
             10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
             63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
             14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

int PC2[] =
{
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

 void print_binary(uint64_t n, int width) {
  for (int i = width - 1; i >= 0; i--) {
    putchar((n & (1ull << i)) ? '1' : '0');
  }
  putchar('\n');
}

uint64_t permute1(uint64_t K, int* table, int table_size) {
    uint64_t permuted_key = 0;
    for (int i = 0; i < table_size; i++) {
        int bit_index = table[i] - 1;
        permuted_key |= ((K >> (64 - bit_index - 1)) & 1) << (table_size - i - 1);
    }
    return permuted_key;
}

uint64_t permute2(uint64_t K, int* table, int table_size) {
    uint64_t permuted_key = 0;
    for (int i = 0; i < table_size; i++) {
        int bit_index = table[i] - 1;
        permuted_key |= ((K >> (64 - bit_index - 1)) & 1) << (table_size - i - 1);
    }
    return permuted_key;
}


int main(int argc, char const *argv[])
{
    uint64_t M = 0x0123456789ABCDEF;
    // scanf("%lu", &num);

    //Each block of 64 bits is divided into two blocks of 32 bits each, a left half block L and a right half R. 

    uint32_t L = (uint32_t)(M >> 32);
    uint32_t R = (uint32_t)(M & 0xFFFFFFFF);

    /*
    M = 0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111

    L = 0000 0001 0010 0011 0100 0101 0110 0111

    R = 1000 1001 1010 1011 1100 1101 1110 1111
    */

    // printf("Left half: %u\nRight half: %u\n", L, R);

    /*
    DES operates on the 64-bit blocks using key sizes of 56- bits. The keys are actually stored as being 64 bits long, but every 8th bit in the key is not used (i.e. bits numbered 8, 16, 24, 32, 40, 48, 56, and 64). However, we will nevertheless number the bits from 1 to 64, going left to right, in the following calculations. But, as you will see, the eight bits just mentioned get eliminated when we create subkeys.
    */

   uint64_t key = 0x133457799BBCDFF1;

   //K = 00010011 00110100 01010111 01111001 10011011 10111100 11011111 11110001

   //Step 1: Create 16 subkeys, each of which is 48-bits long.

    /*
    The 64-bit key is permuted according to the following table, PC-1. Since the first entry in the table is "57", this means that the 57th bit of the original key K becomes the first bit of the permuted key K+. The 49th bit of the original key becomes the second bit of the permuted key. The 4th bit of the original key is the last bit of the permuted key. Note only 56 bits of the original key appear in the permuted key.
    */

    print_binary(key, 64);

    uint64_t permuted_key1 = permute1(key, PC1, 56);
    print_binary(permuted_key1, 56);

    //Next, split this key into left and right halves, C0 and D0, where each half has 28 bits.


    uint32_t c0 = (permuted_key1 >> 28) & 0x0FFFFFFF;
    uint32_t d0 = permuted_key1 & 0x0FFFFFFF;

    print_binary(c0, 28);
    print_binary(d0, 28);
    uint32_t c[17], d[17];
    c[0] = c0;
    d[0] = d0;

    uint64_t Kn[16];

    for (int i = 1; i <= 16; i++) {
        c[i] = ((c[i - 1] << SHIFTS[i - 1]) | (c[i - 1] >> (28 - SHIFTS[i - 1]))) & 0x0FFFFFFF;
        d[i] = ((d[i - 1] << SHIFTS[i - 1]) | (d[i - 1] >> (28 - SHIFTS[i - 1]))) & 0x0FFFFFFF;

        Kn[i-1] = (c[i] << 28) | d[i];

        print_binary(c[i], 28);
        print_binary(d[i], 28);
        printf("\n");
    }


    uint64_t permuted_key2 = permute2(c[1], PC2, 48);
    print_binary(permuted_key2, 48);

    return 0;
}
