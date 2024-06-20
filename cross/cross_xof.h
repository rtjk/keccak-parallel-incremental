#pragma once

#include "cross_fips202.h"

#define XOF_STATE cross_shake256incctx

static inline
void xof_init(XOF_STATE *state) {
    cross_shake256_inc_init(state);
}

static inline
void xof_absorb(XOF_STATE *state, const unsigned char *input, unsigned int inputByteLen) {
    cross_shake256_inc_absorb(state, (const uint8_t *)input, inputByteLen);
}

static inline
void xof_finalize(XOF_STATE *state) {
    cross_shake256_inc_finalize(state);
}

static inline
void xof_squeeze(XOF_STATE *state, unsigned char *output, unsigned int outputByteLen) {
    cross_shake256_inc_squeeze(output, outputByteLen, state);
}

static inline
void xof_release(XOF_STATE *state) {
    //shake256_inc_release(state);
}

static inline
void xof_cycle(
    const unsigned char *input, unsigned int inputByteLen, 
    unsigned char *output, unsigned int outputByteLen) {

    XOF_STATE state;

    xof_init(&state);
    xof_absorb(&state, input, inputByteLen);
    xof_finalize(&state);
    xof_squeeze(&state, output, outputByteLen);
    xof_release(&state);
}

