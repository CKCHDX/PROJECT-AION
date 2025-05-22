#ifndef MEMORY_COMMON_H
#define MEMORY_COMMON_H
#include <stddef.h> 
#include "../Athena/neural.h"

// Shared memory constants
#define MEMORY_OK   0x0
#define MEMORY_ERR  0x1

uint32_t checksum_memory(const void* data, size_t size);

#endif
