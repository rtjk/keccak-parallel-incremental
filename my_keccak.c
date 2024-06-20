
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_keccak.h"
#include "my_constants.h"

// START
// INPUT
// STOP
// OUTPUT
// FREE

void my_keccak_start(my_keccak_context *ctx)
{
    KeccakP1600_Initialize(&ctx->state);
    ctx->offset = 0;
}

void my_keccak_input(my_keccak_context *ctx, const unsigned char *in, unsigned int in_len)
{
    while(in_len + ctx->offset >= RATE) {
        KeccakP1600_AddBytes(&ctx->state, in, ctx->offset, RATE - ctx->offset);
        KeccakP1600_Permute_24rounds(&ctx->state);
        in_len -= RATE - ctx->offset;
        in += RATE - ctx->offset;
        ctx->offset = 0;
    }
    KeccakP1600_AddBytes(&ctx->state, in, ctx->offset, in_len);
    ctx->offset += in_len;
}

void my_keccak_stop(my_keccak_context *ctx)
{
    uint8_t ds = DS;
    if(ctx->offset == RATE-1) {
        ds |= 128;
        KeccakP1600_AddBytes(&ctx->state, &ds, ctx->offset, 1);
    } else {
        KeccakP1600_AddBytes(&ctx->state, &ds, ctx->offset, 1);
        ds = 128;
        KeccakP1600_AddBytes(&ctx->state, &ds, RATE - 1, 1);
    }
    ctx->offset = 0;
}

void my_keccak_output(my_keccak_context *ctx, unsigned char *out, unsigned int out_len)
{
    size_t len;
    if(out_len < ctx->offset) {
        len = out_len;
    } else {
        len = ctx->offset;
    }
    KeccakP1600_ExtractBytes(&ctx->state, out, RATE - ctx->offset, len);
    out += len;
    out_len -= len;
    ctx->offset -= len;

    while(out_len > 0) {
        KeccakP1600_Permute_24rounds(&ctx->state);
        ///////////////////////////////////////
        //for (int i = 0; i < 200; ++i) {printf("%02x", (ctx->state).A[i]);} printf("\n");
        ///////////////////////////////////////
        if(out_len < RATE) {
            len = out_len;
        } else {
            len = RATE;
        }
        KeccakP1600_ExtractBytes(&ctx->state, out, 0, len);
        out += len;
        out_len -= len;
        ctx->offset = RATE - len;
    }
}

///////////////////////////////////////////////////////////////////////////////////

/*
void KeccakP1600_Initialize(KeccakP1600_plain8_state *state);
void KeccakP1600_AddBytes(KeccakP1600_plain8_state *state, const unsigned char *data, unsigned int offset, unsigned int length);
void KeccakP1600_Permute_24rounds(KeccakP1600_plain8_state *state);
void KeccakP1600_ExtractBytes(const KeccakP1600_plain8_state *state, unsigned char *data, unsigned int offset, unsigned int length);
*/

/*

BASED ON CROSS/lib/fips202.c

static void keccak_inc_squeeze(uint8_t *h, size_t outlen,
                               uint64_t *s_inc, uint32_t r)

static void keccak_inc_absorb(uint64_t *s_inc, uint32_t r, const uint8_t *m,
                              size_t mlen)

static void keccak_inc_finalize(uint64_t *s_inc, uint32_t r, uint8_t p)

*/