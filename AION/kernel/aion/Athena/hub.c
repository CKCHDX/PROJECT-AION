#include "hub.h"
#include "../Praxon/brain_stem.h"
#include "memory/memory.h"

void hub_initialize(void) {
    initialize_brain_stem();
    memory_initialize();
    // TODO: initialize other Athena modules
}

void hub_update(void) {
    update_brain_stem();
    // For demonstration, print memory status each cycle
    memory_status();
    // TODO: update other Athena modules
}
