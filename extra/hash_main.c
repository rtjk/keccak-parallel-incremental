#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeccakP-1600-SnP.h"  // Include the XKCP header for Keccak-p functions

#define MESSAGE_MAX_LENGTH 1024  // Maximum length of the message (adjust as needed)
#define HASH_LENGTH 32           // Length of the hash output in bytes

// Function to compute Keccak hash of given length from message
void keccak_hash(const unsigned char *message, size_t length_msg,
                 unsigned char *hash, size_t length_hash) {
    KeccakP1600_plain8_state keccak_state;

    // Initialize Keccak state
    KeccakP1600_Initialize(&keccak_state);

    // Absorb the entire message
    KeccakP1600_AddBytes(&keccak_state, message, 0, (unsigned int)length_msg);

    // Permute the state with 24 rounds (as requested)
    KeccakP1600_Permute_Nrounds(&keccak_state, 24);

    // Squeeze out the hash of desired length
    KeccakP1600_ExtractBytes(&keccak_state, hash, 0, (unsigned int)length_hash);
}

int main() {
    unsigned char message[] = "This is a test input for Keccak hashing.";
    //"Hello, Keccak!";  // Example message
    size_t length_msg = strlen((char *)message);

    unsigned char hash[HASH_LENGTH];

    // Compute the hash
    keccak_hash(message, length_msg, hash, HASH_LENGTH);

    // Print the hash
    printf("Message: %s\n", message);
    printf("Hash (in hexadecimal): ");
    for (int i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
