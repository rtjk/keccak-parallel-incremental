#include <stdio.h>
#include <stdint.h>

#include "my_keccak.h"

//#define IN_LEN 64  // Input length in bytes
#define IN_LEN 10
#define OUT_LEN 32 // Output length in bytes

int main() {

    my_keccak_context ctx;
    my_keccak_start(&ctx);
    unsigned char input[IN_LEN] = "aaaaaaaaaa";
    my_keccak_input(&ctx, input, IN_LEN);
    my_keccak_stop(&ctx);
    unsigned char output[OUT_LEN];
    my_keccak_output(&ctx, output, OUT_LEN);

    printf("Keccak output: ");
    for (int i = 0; i < OUT_LEN; ++i) {
        printf("%02x", output[i]);
    }
    printf("\n");

    return 0;
}
