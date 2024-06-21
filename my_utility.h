#pragma once

#include <stdio.h>
#include "KeccakP-1600-times4-SnP.h"
#include "KeccakP-1600-SnP.h"
#include "cross/cross_fips202.h"

void print_V256(V256 vec) {
    uint8_t values[32];
    _mm256_storeu_si256((__m256i*)values, vec);
    printf("[");
    for (int i = 0; i < 32; i += 4) {
        // Print each 4-byte word in reverse order
        printf("%02x%02x%02x%02x", values[i], values[i + 1], values[i + 2], values[i + 3]);
        if (i < 28) {
            printf(", ");
        }
    }
    printf("]\n");
}

void reset_array(unsigned char *array, unsigned int len) {
    for (unsigned int i = 0; i < len; ++i) {
        array[i] = 0;
    }
}

void fill_array(unsigned char array[], int length) {
    for (int i = 0; i < length; i++) {
        int is_uppercase = rand() % 2; // Randomly choose between uppercase and lowercase
        if (is_uppercase) {
            array[i] = 'A' + (rand() % 26); // Random uppercase letter
        } else {
            array[i] = 'a' + (rand() % 26); // Random lowercase letter
        }
    }
}

void print_state(KeccakP1600_plain8_state state) {
    for (int i = 0; i < 200; ++i) {
        if(i%8 == 0 && i != 0)
            printf("\n");
        else if(i%4 == 0 && i != 0)
            printf(", ");
        printf("%02x", state.A[i]);
    }
    printf("\n");
}

void print_cross_state(cross_shake256incctx state) {
    uint8_t* byte_ptr = (uint8_t*)state.ctx;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 4; k++) {
                printf("%02x", byte_ptr[i * 8 + j * 4 + k]);
            }
            printf(", ");
        }
        printf("\n");
    }
}

void print_states(KeccakP1600times4_SIMD256_states states) {
    for (int i = 0; i < 25; ++i) {
        printf("A[%d] =\t", i);
        print_V256(states.A[i]);
    }
}

void print_array(const unsigned char* array, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X", array[i]);
    }
    printf("\n");
}

void simple_randombytes(unsigned char *x, unsigned long long xlen) {
    for (unsigned long long i = 0; i < xlen; i++) {
        x[i] = (unsigned char) (rand() % 256);
    }
}

void print_progress(int i, int progress) {
    if((i%progress == 0) && i) {
        printf(".");
        fflush(stdout);
    }
}

static void print_short_array(const char *name, unsigned char *array, unsigned long long len) {
    printf("%s: ", name);
    for (size_t i = 0; i < len; i++) {
        if(i < 3) printf("%02x", array[i]);
        else if(i == len/2) printf(" ... ");
        else if(i > (len-4)) printf("%02x", array[i]);
    }
}