#pragma once

#include "cross_fips202.h"

#define XOF_STATE cross_shake256incctx

static inline
void xof_start(XOF_STATE *state) {
    cross_shake256_inc_init(state);
}

static inline
void xof_input(XOF_STATE *state, const unsigned char *input, unsigned int inputByteLen) {
    cross_shake256_inc_absorb(state, (const uint8_t *)input, inputByteLen);
}

static inline
void xof_stop(XOF_STATE *state) {
    cross_shake256_inc_finalize(state);
}

static inline
void xof_output(XOF_STATE *state, unsigned char *output, unsigned int outputByteLen) {
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

    xof_start(&state);
    xof_input(&state, input, inputByteLen);
    xof_stop(&state);
    xof_output(&state, output, outputByteLen);
    xof_release(&state);
}

