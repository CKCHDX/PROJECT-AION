#include "hub.h"
#include "../Praxon/brain_stem.h"
#include "memory/memory.h"
#include "perception/perception.h"
#include "learning/learning.h"
#include "attention/attention.h"
#include "reasoning/reasoning.h"
#include "planning/planning.h"
#include "action/action.h"
#include "language/language_kernel.h"
#include "../hub_vga.h"

void hub_initialize(void) {
    hub_vga_init(9); // Now 9 modules!
    initialize_brain_stem();
    memory_initialize();
    perception_initialize();
    learning_initialize();
    attention_initialize();
    reasoning_initialize();
    planning_initialize();
    action_initialize();
    language_initialize();
}


void hub_update(void) {
    update_brain_stem();

    // Perception -> Memory
    uint8_t buffer[64];
    size_t bytes_read = perception_read(buffer, sizeof(buffer));
    if (bytes_read > 0) {
        memory_store(buffer, bytes_read);
    }

    // Learning
    learning_process();

    // Attention
    AttentionFocus candidates[3] = {
        { .id = 0, .salience = 0.8f },
        { .id = 1, .salience = 0.3f },
        { .id = 2, .salience = 0.9f }
    };
    attention_update(candidates, 3);

    // Reasoning
    reasoning_update();

    planning_update();

    // Action
    action_execute();

    // Language
    language_update();

    // Status reporting (order matters for VGA grid)
    perception_status();
    memory_status();
    learning_status();
    attention_status();
    reasoning_status();
    planning_status();
    action_status();
    language_status();
}