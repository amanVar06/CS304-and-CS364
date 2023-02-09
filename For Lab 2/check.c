#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t K = 0x6B1EB6D8;
    printf("The equivalent hexadecimal value is: %X\n", K);
    uint16_t arr[5];

    arr[0] = (uint16_t)((K >> 16) & 0xFFFF);
    arr[1] = (uint16_t)((K >> 12) & 0xFFFF);
    arr[2] = (uint16_t)((K >> 8) & 0xFFFF);
    arr[3] = (uint16_t)((K >> 4) & 0xFFFF);
    arr[4] = (uint16_t)(K & 0xFFFF);

    for (int i = 0; i < 5; i++) {
        // printf("arr[%d]: %d\n", i, arr[i]);
        printf("K%d = 0x%X\n", i + 1, arr[i]);
    }
    return 0;
}
