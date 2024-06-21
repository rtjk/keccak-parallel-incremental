#include <stdio.h>
#include <stdint.h>
#include "KeccakP-1600-SnP.h"

//#define IN_LEN 64  // Input length in bytes
#define IN_LEN 200  // Input length in bytes
#define OUT_LEN 32 // Output length in bytes

int main() {
    KeccakP1600_plain8_state state;
    KeccakP1600_Initialize(&state);

    // Example input data (replace with actual input)
    unsigned char input[IN_LEN] = "This is a test input for Keccak hashing.";

    // Add input data to the state
    KeccakP1600_AddBytes(&state, input, 0, IN_LEN);

    // Permute the state with 24 rounds
    KeccakP1600_Permute_24rounds(&state);

    unsigned char output[OUT_LEN];
    KeccakP1600_ExtractBytes(&state, output, 0, OUT_LEN);

    // Output the result (example)
    printf("Keccak output: ");
    for (int i = 0; i < OUT_LEN; ++i) {
        printf("%02x", output[i]);
    }
    printf("\n");

    return 0;
}
