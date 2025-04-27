#include <stddef.h>
#include <stdint.h>

#define HEAP_START 0x200000  // 2MB
#define HEAP_SIZE  0x100000  // 1MB

static uint8_t* heap_ptr;
static uint8_t* heap_end;

void init_memory() {
    heap_ptr = (uint8_t*)HEAP_START;
    heap_end = heap_ptr + HEAP_SIZE;
}

void* kmalloc(size_t size) {
    if(heap_ptr + size > heap_end) return NULL;
    void* mem = heap_ptr;
    heap_ptr += size;
    return mem;
}