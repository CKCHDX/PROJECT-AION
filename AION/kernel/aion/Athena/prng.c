#include "prng.h"

static uint32_t prng_state = 0xACE1U;

// Rename functions
void prng_srand(uint32_t seed) {  // WAS: srand()
    prng_state = seed;
}

uint32_t prng_rand(void) {  // WAS: rand()
    prng_state ^= prng_state << 13;
    prng_state ^= prng_state >> 17;
    prng_state ^= prng_state << 5;
    return prng_state;
}

// Add missing xorshift32
uint32_t xorshift32(void) {
    return prng_rand(); // Reuse the same generator
}