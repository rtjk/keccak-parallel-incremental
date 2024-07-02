# keccak-parallel-incremental

An implementation of parallel (x4) Keccak that uses the init-absorb-finalize-squeeze API, where `absorb()` and `squeeze()` can be called multiple times "incrementally". This comes from the need to use 4-way Keccak for hashing and pseudo-random number generation in the signature scheme [CROSS](https://www.cross-crypto.com/).

When compiling on an AVX2 compatible architecture and using flags `-march=native` and `-O3` the parallel version is expected to be more that 3 times faster than the serial one (we can triplicate the number of messages hashed in a certain time interval).

Files of interest:
- `my_par_keccak.h` function declarations
- `my_par_keccak.c` function definitions
- `my_constants.h` defines Keccak's input rates and domain separators
- `main.c` tests hashing random messages to ensure that keccak-x4 gives the same output as the refernce serial (x1) version
- Files imported directly from [XKCP](https://github.com/XKCP/XKCP) and not modified:
    - `KeccakP-1600-times4-SnP.h` the parallel, AVX2-optimized version by the Keccak team, uses the init-addBytes-permute-extractBytes API 
    - `KeccakP-1600-times4-SIMD256.c`
    - `KeccakP-1600-unrolling.macros`
    - `SIMD256-config.h` loop unrolling configuration
    - `align.h`
    - `brg_endian.h`
- `cross/cross_fips202.c` the one-way incremental implementation of Keccak already present in CROSS, on which the parallel version is based

#

```
TODO:
- use main.c to test shake-128 (shake-256 already tested)
- experiemnt with loop unrolling (u6, u12, ua) in SIMD256-config.h
- look for changes in:
  XKCP/lib/low/KeccakP-1600-times4/AVX2
- compare the outputs with keccak-x1 in PQClean and check domain separator padding
- add author and license info in file headers
```
