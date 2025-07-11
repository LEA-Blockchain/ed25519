#include "randombytes.h"
#include "src/monocypher.h"
#include "src/optional/monocypher-ed25519.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlea.h>

#define SEED_BYTES 32
#define PK_BYTES 32
#define SK_BYTES 64
#define SIG_BYTES 64

LEA_EXPORT(keygen)
int keygen(uint8_t *pk, uint8_t *sk)
{
    uint8_t seed[SEED_BYTES];
    randombytes(seed, SEED_BYTES);
    crypto_ed25519_key_pair(sk, pk, seed);
    return 0;
}

LEA_EXPORT(sign)
int sign(uint8_t *sig, const uint8_t *m, size_t mlen, const uint8_t *sk)
{
    crypto_ed25519_sign(sig, sk, m, mlen);
    return 0;
}

LEA_EXPORT(verify)
int verify(const uint8_t *sig, const uint8_t *m, size_t mlen, const uint8_t *pk)
{
    return crypto_ed25519_check(sig, pk, m, mlen);
}

// --- Exported Constants for Buffer Sizes ---
LEA_EXPORT(pk_bytes)
int pk_bytes()
{
    return PK_BYTES;
}

LEA_EXPORT(sk_bytes)
int sk_bytes()
{
    return SK_BYTES;
}

LEA_EXPORT(signature_bytes)
int signature_bytes()
{
    return SIG_BYTES;
}
