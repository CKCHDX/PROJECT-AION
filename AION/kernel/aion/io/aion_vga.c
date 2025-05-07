#include "../aion.h"            // For emergency_shutdown
#include "../security/permissions.h"
#include <stdarg.h>             // For va_list, va_start, va_end

// Define VGA memory location
#define VGA_MEMORY 0xB8000
#define BAD_VGA 0xBADC0DE       // Clearly defined error code

// VGA buffer (volatile to prevent compiler optimization)
static volatile char* vga_buffer = (volatile char*)VGA_MEMORY;

void aion_vga_init() {
    // Check memory boundaries for VGA memory
    if (verify_memory_boundaries((void*)VGA_MEMORY) != 0) {
        emergency_shutdown(BAD_VGA);  // Use BAD_VGA constant for shutdown
    }
}

void aion_vga_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // Basic VGA printing (assuming 80x25 text mode)
    const char* p = fmt;
    while (*p != '\0') {
        *vga_buffer++ = *p++;
        *vga_buffer++ = 0x07;  // White on black text
    }

    va_end(args);
}
