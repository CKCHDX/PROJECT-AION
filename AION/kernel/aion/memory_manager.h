#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h> 

void init_memory_manager();   // Initialize memory manager
void *alloc_memory(size_t size);   // Allocates a block of memory
void free_memory(void *ptr);  // Frees a previously allocated block

#endif
