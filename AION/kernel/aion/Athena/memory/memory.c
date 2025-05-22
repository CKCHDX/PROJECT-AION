#include "memory.h"
#include "../utils.h"
#include "../hub_vga.h"

#define MEMORY_BUFFER_SIZE 4096
static uint8_t memory_buffer[MEMORY_BUFFER_SIZE];
static size_t memory_used = 0;

void memory_initialize(void) {
    for (size_t i = 0; i < MEMORY_BUFFER_SIZE; ++i) memory_buffer[i] = 0;
    memory_used = 0;
    hub_vga_update(HUB_VGA_MODULE_MEMORY, 0, "[MEMORY] Initialized");
}

int memory_store(const void *data, size_t size) {
    if (size > MEMORY_BUFFER_SIZE) return -1;
    if (memory_used + size > MEMORY_BUFFER_SIZE) return -2;
    athena_memcpy(memory_buffer + memory_used, data, size);
    memory_used += size;
    char buf[48];
    athena_snprintf(buf, sizeof(buf), "[MEMORY] Stored %d bytes", (int)size);
    hub_vga_update(HUB_VGA_MODULE_MEMORY, 1, buf);
    return 0;
}

const void* memory_retrieve(size_t *size_out) {
    if (memory_used == 0) {
        *size_out = 0;
        return 0;
    }
    *size_out = memory_used;
    return memory_buffer;
}

void memory_clear(void) {
    for (size_t i = 0; i < MEMORY_BUFFER_SIZE; ++i) memory_buffer[i] = 0;
    memory_used = 0;
    hub_vga_update(HUB_VGA_MODULE_MEMORY, 2, "[MEMORY] Cleared");
}

void memory_status(void) {
    char buf[48];
    athena_snprintf(buf, sizeof(buf), "[MEMORY] %d/%d bytes used", (int)memory_used, MEMORY_BUFFER_SIZE);
    hub_vga_update(HUB_VGA_MODULE_MEMORY, 3, buf);
}
