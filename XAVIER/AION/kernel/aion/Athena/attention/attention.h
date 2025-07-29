#ifndef ATHENA_ATTENTION_H
#define ATHENA_ATTENTION_H

#include <stdint.h>
#include <stddef.h>

#define ATTENTION_MAX_FOCI 7

typedef struct {
    uint8_t id;       // ID of the item in focus (e.g., memory index, perception ID)
    float salience;   // How "attention-grabbing" this item is
    float activation; // How much cognitive resource is allocated
} AttentionFocus;

typedef struct {
    AttentionFocus foci[ATTENTION_MAX_FOCI];
    size_t count;
} AttentionState;

// Initialize the attention system
void attention_initialize(void);

// Update attention based on candidates and their salience
void attention_update(const AttentionFocus* candidates, size_t n);

// Get the current attention state (for other modules)
const AttentionState* attention_get_state(void);

// Print status to VGA or log
void attention_status(void);

#endif // ATHENA_ATTENTION_H
