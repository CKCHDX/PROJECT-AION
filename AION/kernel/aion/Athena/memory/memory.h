#ifndef ATHENA_MEMORY_H
#define ATHENA_MEMORY_H

#include <stddef.h>
#include <stdint.h>

void memory_initialize(void);
int memory_store(const void *data, size_t size);
const void* memory_retrieve(size_t *size_out);
void memory_clear(void);
void memory_status(void);

#endif // ATHENA_MEMORY_H
