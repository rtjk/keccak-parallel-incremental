
#include "KeccakP-1600-SnP.h"

typedef struct {
    KeccakP1600_plain8_state state;
    /* - during absrbtion: "offset" is the number of absorbed bytes that have already been xored into the state but have not been permuted yet
     * - during squeezing: "offset" is the number of not-yet-squeezed bytes */
    uint64_t offset;
} my_keccak_context;

void my_keccak_start(my_keccak_context *ctx);
void my_keccak_input(my_keccak_context *ctx, const unsigned char *in, unsigned int in_len);
void my_keccak_stop(my_keccak_context *ctx);
void my_keccak_output(my_keccak_context *ctx, unsigned char *out, unsigned int out_len);