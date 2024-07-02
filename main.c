#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

//#include "./pqclean/pqclean_fips202.h"
#include "./cross/cross_xof.h"
//#include "my_keccak.h"
#include "my_par_keccak.h"
#include "my_utility.h"

#define NUM_TESTS 10000000
#define PROGRESS 1000
#define IN_LEN 600
#define OUT_LEN 600
#define REPEAT_INPUT 10
#define REPEAT_OUTPUT 10

int main() {
    
    unsigned char ins[4][IN_LEN] = {0};
    unsigned char outs_s[4][OUT_LEN] = {0};
    unsigned char outs_p[4][OUT_LEN] = {0};

    //pqclean_shake256incctx ctx; // pqclean
    XOF_STATE ctx;
    my_par_keccak_context pctx;

    setbuf(stdout, NULL);
    
    for(int test=0; test<NUM_TESTS; test++) {

        /* randomize the input and output length */
        int test_in_len = rand() % IN_LEN;
        int test_out_len = rand() % OUT_LEN;

        /* randomize the number of absorbtions and squeezes */
        int repeat_input = rand() % REPEAT_INPUT;
        int repeat_output = rand() % REPEAT_OUTPUT;

        /* randomize the input buffer */
        for(int i=0; i<4; i++) {
            simple_randombytes(ins[i], test_in_len);
        }
        
        /* call serial keccak on the 4 inputs and get 4 outputs */
        for(int i=0; i<4; i++) {
            xof_start(&ctx);
            for(int j=0; j<repeat_input; j++) xof_input(&ctx, ins[i], test_in_len);
            xof_stop(&ctx);
            for(int j=0; j<repeat_output; j++) xof_output(&ctx, outs_s[i], test_out_len);
        }

        /* call parallel keccak on the 4 inputs and get 4 outputs */
        my_par_keccak_start(&pctx);
        for(int j=0; j<repeat_input; j++) my_par_keccak_input(&pctx, ins[0], ins[1], ins[2], ins[3], test_in_len);
        my_par_keccak_stop(&pctx);
        for(int j=0; j<repeat_output; j++) my_par_keccak_output(&pctx, outs_p[0], outs_p[1], outs_p[2], outs_p[3], test_out_len);

        /* compare the outputs */
        for(int i=0; i<4; i++) {
            if(!memcmp(outs_s[i], outs_p[i], test_out_len) == 0) {
                printf("\n Test %d failed", test);
                printf("\n index: %d, in_len: %d, out_len: %d, absorbtions: %d, squeezes: %d", i, test_in_len, test_out_len, repeat_input, repeat_output);
                print_short_array("\n in   ", ins[i], test_in_len);
                print_short_array("\n out_s", outs_s[i], test_out_len);
                print_short_array("\n out_p", outs_p[i], test_out_len);
                printf("\n");       
                // print_cross_state(ctx);
                // print_states(pctx.state);
                usleep(1000000);
                exit(-1);
            }
        }
        print_progress(test, PROGRESS);
    }
    printf("\n\n");

    return 0;
}

/*
            // pqclean
            pqclean_shake256_inc_init(&ctx);
            for(int j=0; j<repeat_input; j++) pqclean_shake256_inc_absorb(&ctx, ins[i], test_in_len);
            pqclean_shake256_inc_finalize(&ctx);
            for(int j=0; j<repeat_output; j++) pqclean_shake256_inc_squeeze(outs_s[i], test_out_len, &ctx);
            pqclean_shake256_inc_ctx_release(&ctx);
*/