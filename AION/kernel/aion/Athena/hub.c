#include "hub.h"
#include "../Praxon/brain_stem.h"
#include "memory/memory.h"
#include "perception/perception.h"
#include "learning/learning.h"
#include "attention/attention.h" // <-- Add this!
#include "../hub_vga.h"

void hub_initialize(void) {
    hub_vga_init(5); // <-- Now 5 modules!
    initialize_brain_stem();
    memory_initialize();
    perception_initialize();
    learning_initialize();
    attention_initialize(); // <-- Add this!
}

void hub_update(void) {
    update_brain_stem();

    uint8_t buffer[64];
    size_t bytes_read = perception_read(buffer, sizeof(buffer));
    if (bytes_read > 0) {
        memory_store(buffer, bytes_read);
    }

    learning_process();

    // ---- ATTENTION ----
    AttentionFocus candidates[3] = {
        { .id = 0, .salience = 0.8f },
        { .id = 1, .salience = 0.3f },
        { .id = 2, .salience = 0.9f }
    };
    attention_update(candidates, 3);
    attention_status();

    perception_status();
    memory_status();
    learning_status();
}
