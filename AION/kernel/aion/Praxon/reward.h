#ifndef REWARD_H
#define REWARD_H

void reward_system_init(void);
float calculate_reward(unsigned char prev_state, unsigned char action, unsigned char curr_state);

#endif
