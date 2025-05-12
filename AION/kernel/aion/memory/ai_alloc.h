#ifndef AI_ALLOC_H
#define AI_ALLOC_H

#include <stddef.h>

void* ai_malloc(size_t size);
void ai_free(void* ptr);
void memory_firewall_init();

#endif
