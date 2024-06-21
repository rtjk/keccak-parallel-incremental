#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./cross/cross_xof.h"
//#include "my_keccak.h"
#include "my_par_keccak.h"
#include "my_utility.h"

int main() {

    clock_t t_parallel, t_serial, t_total, t_tmp;
    int num_tests = 100000;
    t_total = clock();
    /////////////////////////////////////////////////////////////////////////////////
    int in_len = 64+1;
    int out_len = 64+1;
    unsigned char in1[in_len];
    unsigned char in2[in_len];
    unsigned char in3[in_len];
    unsigned char in4[in_len];
    unsigned char out1[out_len];
    unsigned char out2[out_len];
    unsigned char out3[out_len];
    unsigned char out4[out_len];
    fill_array(in1, in_len);
    fill_array(in2, in_len);
    fill_array(in3, in_len);
    fill_array(in4, in_len);
    // /////////////////////////////////////////////////////////////////////////////////
    // t_serial = clock();
    // my_keccak_context ctx;
    // for(int i=0; i<num_tests; i++) {
    //     in1[3] += 100; // just to change the input
    //     my_keccak_start(&ctx);
    //     my_keccak_input(&ctx, in1, in_len);
    //     my_keccak_stop(&ctx);
    //     my_keccak_output(&ctx, out1, out_len);
    // }
    // t_serial = clock() - t_serial; 
    /////////////////////////////////////////////////////////////////////////////////
    t_serial = clock();
    XOF_STATE ctx;
    for(int i=0; i<num_tests; i++) {
        xof_start(&ctx);
        xof_input(&ctx, in1, in_len);
        xof_stop(&ctx);
        xof_output(&ctx, out1, out_len);
    }
    t_serial = clock() - t_serial;
    print_array(out1, out_len);
    /////////////////////////////////////////////////////////////////////////////////
    //printf("Keccak output: ");for (int i = 0; i < TEST_LEN; ++i) {printf("%02x", test_out[i]);}printf("\n");
    //print_state(ctx.state);
    /////////////////////////////////////////////////////////////////////////////////
    t_parallel = clock();
    my_par_keccak_context pctx;
    for(int i=0; i<num_tests; i++) {
        //in1[3] += 100; // just to change the input
        my_par_keccak_start(&pctx);
        my_par_keccak_input(&pctx, in1, in2, in3, in4, in_len);
        my_par_keccak_stop(&pctx);
        my_par_keccak_output(&pctx, out1, out2, out3, out4, out_len);
    }
    t_parallel = clock() - t_parallel;
    print_array(out1, out_len);
    /////////////////////////////////////////////////////////////////////////////////
    //printf("Keccak output: ");for (int i = 0; i < TEST_LEN; ++i) {printf("%02x", test_out[i]);}printf("\n");
    //print_states(pctx.state);
    /////////////////////////////////////////////////////////////////////////////////
    t_total = clock() - t_total;
    double time_taken = ((double)t_total)/CLOCKS_PER_SEC;
    double percent = ((double)t_parallel - (double)t_serial)/(double)t_serial*100;
    double speedup = (double)t_serial / ((double)t_parallel/4);
    printf("\nSERIAL:\t\t %i cc", t_serial);
    printf("\nPARALLEL:\t %i cc\t%+.2f %%", t_parallel, percent);
    printf("\nSPEEDUP:\t x%.2f", speedup);
    printf("\n******************************************\n");
    printf("Ran %d tests in %.2f seconds\n", num_tests, time_taken);
    printf("Parameters: in_len=%d out_len=%d\n", in_len, out_len);
    printf("******************************************\n");
    return 0;
}

