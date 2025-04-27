#include "io.h"
#include <stdint.h>
#include "memory.h"

#define VGA_ADDR 0xB8000

void capture_frame() {
    // Simple screen buffer capture
    volatile uint16_t* vga = (volatile uint16_t*)VGA_ADDR;
    
    // Store to memory (primitive visual buffer)
    uint16_t* buffer = kmalloc(2000*sizeof(uint16_t));
    
    for(int i = 0; i < 2000; i++) {
        buffer[i] = vga[i];
    }
}

void detect_motion() {
    // Basic frame differencing
    static uint16_t prev_frame[2000];
    uint16_t curr_frame[2000];
    
    // Capture current
    volatile uint16_t* vga = (volatile uint16_t*)VGA_ADDR;
    for(int i = 0; i < 2000; i++) {
        curr_frame[i] = vga[i];
    }
    
    // Compare with previous
    int changes = 0;
    for(int i = 0; i < 2000; i++) {
        if(curr_frame[i] != prev_frame[i]) changes++;
    }
    
    // Update previous
    for(int i = 0; i < 2000; i++) {
        prev_frame[i] = curr_frame[i];
    }
    
    // Simple VGA output
    if(changes > 100) {
        volatile char* msg = (volatile char*)VGA_ADDR + 320; // 3rd line
        *msg++ = 'M'; *msg++ = 0x0C;  // Red 'M' for motion
    }
}