#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>

uint32_t roundFunction(uint32_t L0, uint32_t K) {
    uint32_t ans;
    uint64_t temp = (uint64_t) (L0 ^ K) * (uint64_t) (L0 ^ K);
    // uint64_t two32 = (uint64_t) 1 <<  (uint64_t) 32;

    // ans = (uint32_t)(temp % two32);
    ans = (uint32_t)(temp & 0xFFFFFFFF); //similar to mod with 2^32 i.e. Lease significant 32 bits
    // ans = (uint32_t)(temp % 4294967296ull);
    return ans;
}

uint64_t decrypt(uint64_t cipher, uint32_t key) {
    uint32_t L_1, R_1, L_0, R_0, K;
    uint64_t P;

    L_1 = (uint32_t)(cipher >> 32);
    R_1 = (uint32_t)(cipher & 0xFFFFFFFF);

    R_0 = L_1;
    L_0 = roundFunction(L_1, key);

    P = L_0;
    P = (P << 32) | R_0;

    return P;
}



int main(int argc, char const *argv[])
{
    uint64_t num;
    scanf("%lu", &num);

    uint32_t left_half = (uint32_t)(num >> 32);
    uint32_t right_half = (uint32_t)(num & 0xFFFFFFFF);

    printf("Left half: %u\nRight half: %u\n", left_half, right_half);

    // uint32_t key = (uint32_t) 0x6575FEAC;
    uint32_t key = (uint32_t) 0x0000000AA;

    printf("After Using Round Function: %u\n", roundFunction(left_half, key));


    uint32_t L1, R1;
    L1 = right_half;
    R1 = roundFunction(left_half, key);

    uint64_t cipher;

    cipher = L1;
    cipher = (cipher << 32) | R1;

    printf("Cipher Text: %lu\n", cipher);
    printf("plain text: %lu\n", decrypt(cipher, key));

    return 0;
}
