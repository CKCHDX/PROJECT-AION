// experience.h
#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include "../brain/neural.h"  // Get INPUT_SIZE

#define STATE_SIZE INPUT_SIZE  // Align with neural input
#define EXPERIENCE_SIZE 1000

struct Experience {
    float state[STATE_SIZE];
    float action;
    float reward;
    float next_state[STATE_SIZE];
    uint8_t terminal;  // Add terminal state flag
};
extern struct Experience experience_buffer[EXPERIENCE_SIZE];
void store_experience(struct Experience exp);

#endif