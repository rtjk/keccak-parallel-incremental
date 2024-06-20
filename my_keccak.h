
#include "KeccakP-1600-SnP.h"

typedef struct {
    KeccakP1600_plain8_state state;
    uint64_t offset; // number of non-absorbed bytes that have already been xored into the state
} my_keccak_context;

void my_keccak_start(my_keccak_context *ctx);
void my_keccak_input(my_keccak_context *ctx, const unsigned char *in, unsigned int in_len);
void my_keccak_stop(my_keccak_context *ctx);
void my_keccak_output(my_keccak_context *ctx, unsigned char *out, unsigned int out_len);