#ifndef RANDOMBYTES_H
#define RANDOMBYTES_H

#ifdef __wasm32__
#include <stdlea.h>
LEA_IMPORT(env, __lea_randombytes) void randombytes(unsigned char *x, unsigned long long xlen);
#else
extern void randombytes(unsigned char *x, unsigned long long xlen);
#endif

#endif
