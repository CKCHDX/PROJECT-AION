// in ai_alloc.h
#define BAD_MEMORY_ADDRESS  0xDEADBEEF  /* or 0xBADADD, whatever you prefer */

// in ai_alloc.c
#include "ai_alloc.h"
#include "../security/permissions.h"

#define AI_MEMORY_POOL_SIZE 1048576  // 1MB

static unsigned char  memory_pool[AI_MEMORY_POOL_SIZE];
static unsigned long  current_offset = 0;

void memory_firewall_init() {
    current_offset = 0;
}

void* ai_malloc(size_t size) {
    if (current_offset + size > AI_MEMORY_POOL_SIZE)
        return NULL;

    void* ptr = &memory_pool[current_offset];
    current_offset += size;

    if (verify_memory_boundaries(ptr) != 0) {
        emergency_shutdown(BAD_MEMORY_ADDRESS);
    }

    return ptr;
}

void ai_free(void* ptr) {
    // Simple allocator – no freeing for now
}
