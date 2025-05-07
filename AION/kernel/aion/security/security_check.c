#include "permissions.h"
#include "../../vga.h"

// In permissions.h
#define AI_ALLOWED_MEMORY_START 0x00010000  // Start after bootloader
#define AI_ALLOWED_MEMORY_END   0x00100000  // 1MB limit
#define VGA_BUFFER_START        0xB8000
#define VGA_BUFFER_END          0xB8FA0


// Critical hardware validation
int validate_hardware_environment() {
    vga_write_at("CPU Check: ", 0x0F, 0, 3);

    // Check CPUID
    unsigned int max_cpuid;
    asm volatile ("cpuid" : "=a"(max_cpuid) : "a"(0x0));
    if(max_cpuid < 0x1) {
        vga_write_at("FAIL (No CPUID)", 0x0C, 11, 3);
        return -1;
    }
    vga_write_at("PASS", 0x0A, 11, 3);

    vga_write_at("Protected Mode: ", 0x0F, 0, 4);
    unsigned int cr0;
    asm volatile ("mov %%cr0, %0" : "=r"(cr0));
    if(!(cr0 & 0x1)) {
        vga_write_at("FAIL", 0x0C, 16, 4);
        return -3;
    }
    vga_write_at("PASS", 0x0A, 16, 4);

    vga_write_at("Memory Regions: ", 0x0F, 0, 5);
    if(verify_memory_boundaries((void*)0xB8000) != 0) {
        vga_write_at("FAIL (VGA Access)", 0x0C, 16, 5);
        return -4;
    }
    vga_write_at("PASS", 0x0A, 16, 5);

    return 0;
}

// Memory boundary verification
int verify_memory_boundaries(void* ptr) {
    unsigned long address = (unsigned long)ptr;
    return (address >= AI_ALLOWED_MEMORY_START &&
    address <= AI_ALLOWED_MEMORY_END) ? 0 : -1;
}
