#include "../vga.h"
#include "memory_manager.h"

#define MEMORY_SIZE 0x100000    // 1MB of memory for simplicity
#define BLOCK_SIZE  0x1000     // 4KB blocks

static char memory_pool[MEMORY_SIZE];  // Our "heap" memory area
static int block_status[MEMORY_SIZE / BLOCK_SIZE];  // 0 = free, 1 = allocated

void init_memory_manager() {
    vga_write("[*] Initializing memory manager...\n");
    for (int i = 0; i < MEMORY_SIZE / BLOCK_SIZE; i++) {
        block_status[i] = 0;  // Mark all blocks as free
    }
    vga_write("[*] Memory manager initialized.\n");
}

void *alloc_memory(size_t size) {
    // Round size up to nearest block size
    size = (size + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1);

    // Find the first free block that fits the requested size
    for (int i = 0; i < MEMORY_SIZE / BLOCK_SIZE; i++) {
        if (block_status[i] == 0 && size <= (MEMORY_SIZE - (i * BLOCK_SIZE))) {
            // Mark the block as allocated
            block_status[i] = 1;
            return &memory_pool[i * BLOCK_SIZE];  // Return the address of the block
        }
    }

    return NULL;  // No free block found
}

void free_memory(void *ptr) {
    int block_idx = ((char *)ptr - memory_pool) / BLOCK_SIZE;
    if (block_idx >= 0 && block_idx < MEMORY_SIZE / BLOCK_SIZE) {
        block_status[block_idx] = 0;  // Mark the block as free
    }
}
