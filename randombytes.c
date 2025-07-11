#include "randombytes.h"
#include <stdint.h>

#ifndef __wasm32__
#warning "[WARNING] Unsecure random generator used in target !!!"
void randombytes(unsigned char *x, unsigned long long xlen)
{
    // Static state for the LFSR. It must be seeded with a non-zero value.
    static uint32_t lfsr_state = 0;

    // Static buffer to hold the bytes from a 32-bit random number.
    static uint8_t byte_buffer[4];
    static int byte_index = 4; // Start at 4 to force a new number generation on first run

    // Seed the LFSR state if it has not been initialized.
    // Any non-zero seed will work.
    if (lfsr_state == 0)
    {
        lfsr_state = 0xACE1u; // A classic, non-zero seed
    }

    for (unsigned long long i = 0; i < xlen; ++i)
    {
        // If we have used all the bytes from our last 32-bit number, generate a new one.
        if (byte_index >= 4)
        {
            // This is the Galois LFSR algorithm.
            // It uses a polynomial mask for a maximal-length sequence.
            uint32_t lsb = lfsr_state & 1; // Get the least significant bit
            lfsr_state >>= 1;              // Shift the state to the right
            if (lsb == 1)
            {
                // If the output bit was 1, XOR the state with the polynomial mask.
                // 0x80200003u is a common primitive polynomial for 32 bits.
                lfsr_state ^= 0x80200003u;
            }

            // Store the new 32-bit random number in our byte buffer
            byte_buffer[0] = (uint8_t)(lfsr_state >> 0);
            byte_buffer[1] = (uint8_t)(lfsr_state >> 8);
            byte_buffer[2] = (uint8_t)(lfsr_state >> 16);
            byte_buffer[3] = (uint8_t)(lfsr_state >> 24);
            byte_index = 0;
        }

        // Provide the next byte from the buffer.
        x[i] = byte_buffer[byte_index++];
    }
}
#endif
