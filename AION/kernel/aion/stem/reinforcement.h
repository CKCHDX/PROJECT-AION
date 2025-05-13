#ifndef REINFORCEMENT_H
#define REINFORCEMENT_H

#include "../memory/experience.h"  // For Experience struct

// Function declarations
struct Experience sample_experience(void);
float max_q_value(const float state[STATE_SIZE]);
float get_q_value(const float state[STATE_SIZE], float action);
float calculate_reward(void);
void q_learning_update(void);
void update_q_value(const float state[STATE_SIZE], float action, float new_value);

#endif // REINFORCEMENT_H