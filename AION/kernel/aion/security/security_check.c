#include "permissions.h"

// In permissions.h
#define AI_ALLOWED_MEMORY_START 0x00010000  // Start after bootloader
#define AI_ALLOWED_MEMORY_END   0x00100000  // 1MB limit
#define VGA_BUFFER_START        0xB8000
#define VGA_BUFFER_END          0xB8FA0


// Critical hardware validation
int validate_hardware_environment() {
    // 1. Check CPU features more safely
    unsigned int max_cpuid;
    asm volatile ("cpuid" : "=a"(max_cpuid) : "a"(0x0));
    if(max_cpuid < 0x1) return -1; // Too old CPU

    // 2. Remove temperature check for now (QEMU doesn't emulate it properly)
    // 3. Check protected mode actually works
    unsigned int cr0;
    asm volatile ("mov %%cr0, %0" : "=r"(cr0));
    if(!(cr0 & 0x1)) return -3; // Not in protected mode

    return 0; // All checks passed
}

// Memory boundary verification
int verify_memory_boundaries(void* ptr) {
    unsigned long address = (unsigned long)ptr;
    return (address >= AI_ALLOWED_MEMORY_START &&
    address <= AI_ALLOWED_MEMORY_END) ? 0 : -1;
}
