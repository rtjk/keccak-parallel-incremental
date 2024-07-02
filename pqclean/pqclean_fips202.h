#ifndef FIPS202_H
#define FIPS202_H

#include <stddef.h>
#include <stdint.h>

#define PQCLEAN_SHAKE128_RATE 168
#define PQCLEAN_SHAKE256_RATE 136
#define PQCLEAN_SHA3_256_RATE 136
#define PQCLEAN_SHA3_384_RATE 104
#define PQCLEAN_SHA3_512_RATE 72

#define PQC_SHAKEINCCTX_BYTES (sizeof(uint64_t)*26)
#define PQC_SHAKECTX_BYTES (sizeof(uint64_t)*25)

// Context for incremental API
typedef struct {
    uint64_t *ctx;
} pqclean_shake128incctx;

// Context for non-incremental API
typedef struct {
    uint64_t *ctx;
} pqclean_shake128ctx;

// Context for incremental API
typedef struct {
    uint64_t *ctx;
} pqclean_shake256incctx;

// Context for non-incremental API
typedef struct {
    uint64_t *ctx;
} pqclean_shake256ctx;

// Context for incremental API
typedef struct {
    uint64_t *ctx;
} pqclean_sha3_256incctx;

// Context for incremental API
typedef struct {
    uint64_t *ctx;
} pqclean_sha3_384incctx;

// Context for incremental API
typedef struct {
    uint64_t *ctx;
} pqclean_sha3_512incctx;

/* Initialize the state and absorb the provided input.
 *
 * This function does not support being called multiple times
 * with the same state.
 */
void pqclean_shake128_absorb(pqclean_shake128ctx *state, const uint8_t *input, size_t inlen);
/* Squeeze output out of the sponge.
 *
 * Supports being called multiple times
 */
void pqclean_shake128_squeezeblocks(uint8_t *output, size_t nblocks, pqclean_shake128ctx *state);
/* Free the state */
void pqclean_shake128_ctx_release(pqclean_shake128ctx *state);
/* Copy the state. */
void pqclean_shake128_ctx_clone(pqclean_shake128ctx *dest, const pqclean_shake128ctx *src);

/* Initialize incremental hashing API */
void pqclean_shake128_inc_init(pqclean_shake128incctx *state);
/* Absorb more information into the XOF.
 *
 * Can be called multiple times.
 */
void pqclean_shake128_inc_absorb(pqclean_shake128incctx *state, const uint8_t *input, size_t inlen);
/* Finalize the XOF for squeezing */
void pqclean_shake128_inc_finalize(pqclean_shake128incctx *state);
/* Squeeze output out of the sponge.
 *
 * Supports being called multiple times
 */
void pqclean_shake128_inc_squeeze(uint8_t *output, size_t outlen, pqclean_shake128incctx *state);
/* Copy the context of the PQCLEAN_SHAKE128 XOF */
void pqclean_shake128_inc_ctx_clone(pqclean_shake128incctx *dest, const pqclean_shake128incctx *src);
/* Free the context of the PQCLEAN_SHAKE128 XOF */
void pqclean_shake128_inc_ctx_release(pqclean_shake128incctx *state);

/* Initialize the state and absorb the provided input.
 *
 * This function does not support being called multiple times
 * with the same state.
 */
void pqclean_shake256_absorb(pqclean_shake256ctx *state, const uint8_t *input, size_t inlen);
/* Squeeze output out of the sponge.
 *
 * Supports being called multiple times
 */
void pqclean_shake256_squeezeblocks(uint8_t *output, size_t nblocks, pqclean_shake256ctx *state);
/* Free the context held by this XOF */
void pqclean_shake256_ctx_release(pqclean_shake256ctx *state);
/* Copy the context held by this XOF */
void pqclean_shake256_ctx_clone(pqclean_shake256ctx *dest, const pqclean_shake256ctx *src);

/* Initialize incremental hashing API */
void pqclean_shake256_inc_init(pqclean_shake256incctx *state);
void pqclean_shake256_inc_absorb(pqclean_shake256incctx *state, const uint8_t *input, size_t inlen);
/* Prepares for squeeze phase */
void pqclean_shake256_inc_finalize(pqclean_shake256incctx *state);
/* Squeeze output out of the sponge.
 *
 * Supports being called multiple times
 */
void pqclean_shake256_inc_squeeze(uint8_t *output, size_t outlen, pqclean_shake256incctx *state);
/* Copy the state */
void pqclean_shake256_inc_ctx_clone(pqclean_shake256incctx *dest, const pqclean_shake256incctx *src);
/* Free the state */
void pqclean_shake256_inc_ctx_release(pqclean_shake256incctx *state);

/* One-stop PQCLEAN_SHAKE128 call */
void pqclean_shake128(uint8_t *output, size_t outlen,
              const uint8_t *input, size_t inlen);

/* One-stop PQCLEAN_SHAKE256 call */
void pqclean_shake256(uint8_t *output, size_t outlen,
              const uint8_t *input, size_t inlen);

/* Initialize the incremental hashing state */
void pqclean_sha3_256_inc_init(pqclean_sha3_256incctx *state);
/* Absorb blocks into PQCLEAN_SHA3 */
void pqclean_sha3_256_inc_absorb(pqclean_sha3_256incctx *state, const uint8_t *input, size_t inlen);
/* Obtain the output of the function and free `state` */
void pqclean_sha3_256_inc_finalize(uint8_t *output, pqclean_sha3_256incctx *state);
/* Copy the context */
void pqclean_sha3_256_inc_ctx_clone(pqclean_sha3_256incctx *dest, const pqclean_sha3_256incctx *src);
/* Release the state, don't use if `_finalize` has been used */
void pqclean_sha3_256_inc_ctx_release(pqclean_sha3_256incctx *state);

void pqclean_sha3_256(uint8_t *output, const uint8_t *input, size_t inlen);

/* Initialize the incremental hashing state */
void pqclean_sha3_384_inc_init(pqclean_sha3_384incctx *state);
/* Absorb blocks into PQCLEAN_SHA3 */
void pqclean_sha3_384_inc_absorb(pqclean_sha3_384incctx *state, const uint8_t *input, size_t inlen);
/* Obtain the output of the function and free `state` */
void pqclean_sha3_384_inc_finalize(uint8_t *output, pqclean_sha3_384incctx *state);
/* Copy the context */
void pqclean_sha3_384_inc_ctx_clone(pqclean_sha3_384incctx *dest, const pqclean_sha3_384incctx *src);
/* Release the state, don't use if `_finalize` has been used */
void pqclean_sha3_384_inc_ctx_release(pqclean_sha3_384incctx *state);

/* One-stop PQCLEAN_SHA3-384 shop */
void pqclean_sha3_384(uint8_t *output, const uint8_t *input, size_t inlen);

/* Initialize the incremental hashing state */
void pqclean_sha3_512_inc_init(pqclean_sha3_512incctx *state);
/* Absorb blocks into PQCLEAN_SHA3 */
void pqclean_sha3_512_inc_absorb(pqclean_sha3_512incctx *state, const uint8_t *input, size_t inlen);
/* Obtain the output of the function and free `state` */
void pqclean_sha3_512_inc_finalize(uint8_t *output, pqclean_sha3_512incctx *state);
/* Copy the context */
void pqclean_sha3_512_inc_ctx_clone(pqclean_sha3_512incctx *dest, const pqclean_sha3_512incctx *src);
/* Release the state, don't use if `_finalize` has been used */
void pqclean_sha3_512_inc_ctx_release(pqclean_sha3_512incctx *state);

/* One-stop PQCLEAN_SHA3-512 shop */
void pqclean_sha3_512(uint8_t *output, const uint8_t *input, size_t inlen);

#endif
