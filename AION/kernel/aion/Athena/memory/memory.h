#ifndef ATHENA_MEMORY_H
#define ATHENA_MEMORY_H

#include <stddef.h>
#include <stdint.h>

// Initialize memory system (buffers, pointers, etc.)
void memory_initialize(void);

// Store a block of data in memory (returns 0 on success)
int memory_store(const void *data, size_t size);

// Retrieve the latest block of data (returns pointer, NULL if empty)
const void* memory_retrieve(size_t *size_out);

// Clear all memory buffers
void memory_clear(void);

// Debug: print memory status using kernel output
void memory_status(void);

#endif // ATHENA_MEMORY_H
