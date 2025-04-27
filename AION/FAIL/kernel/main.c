#include <stdint.h>
#include "io.h"
#include "memory.h"
#include "vision.h"
#include "serial.h"
void print(const char* str) { /* existing */ }

void panic(const char* msg) {
    volatile char* vga = (volatile char*)0xB8000;
    const char* s = "PANIC: ";
    // Write panic message to screen
    while(*s) { *vga++ = *s++; *vga++ = 0x4F; }
    while(*msg) { *vga++ = *msg++; *vga++ = 0x4F; }
    for(;;) __asm__ volatile ("hlt");
}

void kmain() {
    init_serial();
    serial_putc('A'); // Test serial output
    
    // If we get here, basic init worked
    print("AION KERNEL BOOTED.");
    
    // Main cognitive loop
    while(1) {
        blind_io_probe();
        capture_frame();
        detect_motion();
        __asm__ volatile ("hlt");
    }
}