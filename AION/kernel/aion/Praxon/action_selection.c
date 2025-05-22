#include "action_selection.h"
#include "q_learning.h"
#include "state.h"

// Simple pseudo-random generator for demo
static uint32_t prng_state = 123456789;
static uint32_t prng(void) {
    prng_state ^= prng_state << 13;
    prng_state ^= prng_state >> 17;
    prng_state ^= prng_state << 5;
    return prng_state;
}

uint8_t select_action(uint8_t state) {
    float r = (float)(prng() % 10000) / 10000.0f;
    if (r < epsilon)
        return prng() % MAX_ACTIONS;
    else
        return get_best_action(state);
}
