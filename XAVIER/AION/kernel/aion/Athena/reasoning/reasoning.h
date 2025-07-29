#ifndef ATHENA_REASONING_H
#define ATHENA_REASONING_H

#include "../attention/attention.h"
#include "../memory/memory.h"

#define MAX_REASONING_RULES 8

typedef struct {
    uint8_t condition_id;
    uint8_t action_id;
} ReasoningRule;

void reasoning_initialize(void);
void reasoning_update(void);
void reasoning_status(void);
uint8_t reasoning_get_current_action(void);

#endif
