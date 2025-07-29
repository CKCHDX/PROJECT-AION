#include "experience.h"
#include "../Athena/neural.h"
#include "../security/security.h"

struct Experience experience_buffer[EXPERIENCE_SIZE];
static unsigned experience_count = 0;

// Forward declaration of the is_terminal_state function
static uint8_t is_terminal_state(const float* state);

void store_experience(struct Experience exp) {
    exp.terminal = is_terminal_state(exp.next_state);
    
    if(experience_count < EXPERIENCE_SIZE) {
        experience_buffer[experience_count++] = exp;
    } else {
        // Overwrite oldest entry
        for(int i = 0; i < EXPERIENCE_SIZE-1; i++)
            experience_buffer[i] = experience_buffer[i+1];
        experience_buffer[EXPERIENCE_SIZE-1] = exp;
    }
}

static uint8_t is_terminal_state(const float* state) {
    // Example: Terminate if all state values are zero
    for(int i = 0; i < STATE_SIZE; i++) {
        if(state[i] != 0.0f) return 0;
    }
    return 1;
}

struct Experience sample_experience() {
    if(experience_count == 0) {
        emergency_shutdown(0xBADF00D);
    }
    
    // Weighted sampling towards recent experiences
    unsigned idx = xorshift32() % experience_count;
    if(experience_count > 100) {
        idx = (idx + experience_count - 100) % experience_count;
    }
    
    return experience_buffer[idx];
}
