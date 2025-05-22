#include "hub.h"
#include "../Praxon/brain_stem.h"
#include "memory/memory.h"
#include "perception/perception.h"

void hub_initialize(void) {
    initialize_brain_stem();
    memory_initialize();
    perception_initialize();
    // TODO: initialize other Athena modules
}

void hub_update(void) {
    update_brain_stem();

    // Perception: Read data into memory buffer
    uint8_t buffer[64];
    size_t bytes_read = perception_read(buffer, sizeof(buffer));
    if (bytes_read > 0) {
        memory_store(buffer, bytes_read);
    }

    perception_status();
    memory_status();
    // TODO: update other Athena modules
}
