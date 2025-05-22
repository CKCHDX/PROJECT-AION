#include "memory.h"
#include "../utils.h"

// Use your kernel's output function
extern void vga_printf(const char *fmt, ...);

#define MEMORY_BUFFER_SIZE 4096
static uint8_t memory_buffer[MEMORY_BUFFER_SIZE];
static size_t memory_used = 0;

void memory_initialize(void) {
    for (size_t i = 0; i < MEMORY_BUFFER_SIZE; ++i) memory_buffer[i] = 0;
    memory_used = 0;
    vga_printf("[ATHENA][MEMORY] Memory initialized (size: %d bytes)\n", MEMORY_BUFFER_SIZE);
}

int memory_store(const void *data, size_t size) {
    if (size > MEMORY_BUFFER_SIZE) return -1;
    if (memory_used + size > MEMORY_BUFFER_SIZE) return -2;
    athena_memcpy(memory_buffer + memory_used, data, size);
    memory_used += size;
    vga_printf("[ATHENA][MEMORY] Stored %d bytes (used: %d)\n", (int)size, (int)memory_used);
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
    vga_printf("[ATHENA][MEMORY] Memory cleared\n");
}

void memory_status(void) {
    vga_printf("[ATHENA][MEMORY] Status: %d/%d bytes used\n", (int)memory_used, MEMORY_BUFFER_SIZE);
}
