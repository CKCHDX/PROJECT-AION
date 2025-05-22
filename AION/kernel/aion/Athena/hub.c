#include "hub.h"
#include "../Praxon/brain_stem.h"
#include "memory/memory.h"
#include "perception/perception.h"
#include "learning/learning.h"
#include "../hub_vga.h"

void hub_initialize(void) {
    hub_vga_init(4); // MEMORY, LEARNING, PERCEPTION, STEM
    initialize_brain_stem();
    memory_initialize();
    perception_initialize();
    learning_initialize();
}

void hub_update(void) {
    // No vga_clear() here!
    update_brain_stem();

    uint8_t buffer[64];
    size_t bytes_read = perception_read(buffer, sizeof(buffer));
    if (bytes_read > 0) {
        memory_store(buffer, bytes_read);
    }

    learning_process();

    perception_status();
    memory_status();
    learning_status();
}
