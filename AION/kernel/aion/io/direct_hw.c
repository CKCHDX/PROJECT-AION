#include "../security/permissions.h"

// AT&T syntax version
unsigned int read_hardware(unsigned int device_id) {
    unsigned int value;
    __asm__ volatile (
        "inl %%dx, %%eax"
        : "=a" (value)
        : "d" ((unsigned short)device_id)
    );
    return value;
}

void write_hardware(unsigned int device_id, unsigned int value) {
    unsigned short port = (unsigned short)device_id;
    __asm__ volatile (
        "outl %%eax, %%dx"
        :
        : "d" (port), "a" (value)
    );
}
