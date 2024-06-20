#pragma once

#include <stddef.h>
#include <stdint.h>

#define SHAKE128_RATE (168)
#define SHAKE256_RATE (136)
#define SHA3_256_RATE (136)
#define SHA3_384_RATE (104)
#define SHA3_512_RATE ( 72)


// Context for incremental API
typedef struct {
   uint64_t ctx[26];
} cross_shake128incctx;

// Context for non-incremental API
typedef struct {
   uint64_t ctx[25];
} cross_shake128ctx;

// Context for incremental API
typedef struct {
   uint64_t ctx[26];
} cross_shake256incctx;

// Context for non-incremental API
typedef struct {
   uint64_t ctx[25];
} cross_shake256ctx;

// Context for incremental API
typedef struct {
   uint64_t ctx[26];
} sha3_256incctx;

// Context for incremental API
typedef struct {
   uint64_t ctx[26];
} sha3_384incctx;

// Context for incremental API
typedef struct {
   uint64_t ctx[26];
} sha3_512incctx;

/* Initialize the state and absorb the provided input.
 * This function does not support being called multiple times
 * with the same state. */
void cross_shake128_absorb(cross_shake128ctx *state, const uint8_t *input, size_t inlen);
/* Squeeze output out of the sponge.
 * Supports being called multiple times */
void cross_shake128_squeezeblocks(uint8_t *output, size_t nblocks,
                            cross_shake128ctx *state);


/* Initialize incremental hashing API */
void cross_shake128_inc_init(cross_shake128incctx *state);
/* Absorb more information into the XOF.
 * Can be called multiple times. */
void cross_shake128_inc_absorb(cross_shake128incctx *state, const uint8_t *input,
                         size_t inlen);
/* Finalize the XOF for squeezing */
void cross_shake128_inc_finalize(cross_shake128incctx *state);
/* Squeeze output out of the sponge.
 * Supports being called multiple times */
void cross_shake128_inc_squeeze(uint8_t *output, size_t outlen,
                          cross_shake128incctx *state);


/* Initialize the state and absorb the provided input.
 * This function does not support being called multiple times
 * with the same state. */
void cross_shake256_absorb(cross_shake256ctx *state, const uint8_t *input, size_t inlen);
/* Squeeze output out of the sponge.
 * Supports being called multiple times */
void cross_shake256_squeezeblocks(uint8_t *output, size_t nblocks,
                            cross_shake256ctx *state);

/* Initialize incremental hashing API */
void cross_shake256_inc_init(cross_shake256incctx *state);
void cross_shake256_inc_absorb(cross_shake256incctx *state, const uint8_t *input,
                         size_t inlen);
/* Prepares for squeeze phase */
void cross_shake256_inc_finalize(cross_shake256incctx *state);
/* Squeeze output out of the sponge.
 * Supports being called multiple times */
void cross_shake256_inc_squeeze(uint8_t *output, size_t outlen,
                          cross_shake256incctx *state);


/* One-stop SHAKE128 call */
void cross_shake128(uint8_t *output, size_t outlen, const uint8_t *input,
              size_t inlen);
/* One-stop SHAKE256 call */
void cross_shake256(uint8_t *output, size_t outlen, const uint8_t *input,
              size_t inlen);

/* Initialize the incremental hashing state */
void sha3_256_inc_init(sha3_256incctx *state);
/* Absorb blocks into SHA3 */
void sha3_256_inc_absorb(sha3_256incctx *state, const uint8_t *input,
                         size_t inlen);
/* Obtain the output of the function and free `state` */
void sha3_256_inc_finalize(uint8_t *output, sha3_256incctx *state);
/* One-stop SHA3-256 shop */
void sha3_256(uint8_t *output, const uint8_t *input, size_t inlen);

/* Initialize the incremental hashing state */
void sha3_384_inc_init(sha3_384incctx *state);
/* Absorb blocks into SHA3 */
void sha3_384_inc_absorb(sha3_384incctx *state, const uint8_t *input,
                         size_t inlen);
/* Obtain the output of the function and free `state` */
void sha3_384_inc_finalize(uint8_t *output, sha3_384incctx *state);
/* One-stop SHA3-384 shop */
void sha3_384(uint8_t *output, const uint8_t *input, size_t inlen);

/* Initialize the incremental hashing state */
void sha3_512_inc_init(sha3_512incctx *state);
/* Absorb blocks into SHA3 */
void sha3_512_inc_absorb(sha3_512incctx *state, const uint8_t *input,
                         size_t inlen);
/* Obtain the output of the function and free `state` */
void sha3_512_inc_finalize(uint8_t *output, sha3_512incctx *state);
/* One-stop SHA3-512 shop */
void sha3_512(uint8_t *output, const uint8_t *input, size_t inlen);
