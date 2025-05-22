#include "reward.h"

void reward_system_init(void) {}

float calculate_reward(unsigned char prev_state, unsigned char action, unsigned char curr_state) {
    // Example reward: +1 for state change, -0.1 otherwise
    return (prev_state != curr_state) ? 1.0f : -0.1f;
}
