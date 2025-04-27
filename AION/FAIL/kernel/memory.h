#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void init_memory(void);
void* kmalloc(size_t size);

#endif