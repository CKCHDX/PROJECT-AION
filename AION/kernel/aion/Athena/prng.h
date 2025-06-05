// kernel/aion/brain/prng.h
#ifndef PRNG_H
#define PRNG_H

#include <stdint.h>

#define RAND_MAX 0xFFFFFFFF  // Explicit 32-bit maximum

// Proper function declarations
void srand(uint32_t seed);
uint32_t rand(void);
uint32_t xorshift32(void);

#endif