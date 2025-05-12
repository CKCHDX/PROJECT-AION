#include "memory_common.h"
#include <stddef.h>  // Include this to define size_t

uint32_t checksum_memory(const void* data, size_t size) {
    const uint8_t* bytes = data;
    uint32_t sum = 0;
    for(size_t i = 0; i < size; i++) {
        sum = (sum << 3) ^ bytes[i];
    }
    return sum;
}
