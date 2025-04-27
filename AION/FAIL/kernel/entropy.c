#include <stdint.h>
#include <stddef.h>
#include "io.h"
#include "memory.h"

#define ENTROPY_THRESHOLD 3.5
#define VGA_BASE 0xB8000

// Convert nibble to hex char
static char nibble_to_hex(uint8_t nibble) {
    return (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
}

static double log2(double x) {
    if(x <= 0) return 0;
    
    union {
        double d;
        uint64_t i;
    } u;
    
    u.d = x;
    int exponent = (int)((u.i >> 52) & 0x7FF);  // Added missing parenthesis
    return (double)(exponent - 1023);
}


// Display port and entropy on VGA (row 2)
void log_entropy(uint16_t port, double entropy) {
    volatile char* vga = (volatile char*)(VGA_BASE + 160); // Row 2
    
    // Write 'PORT 0x'
    const char prefix[] = "PORT 0x";
    for(int i=0; i<7; i++) {
        *vga++ = prefix[i];
        *vga++ = 0x0A; // Green text
    }
    
    // Write port in hex (4 digits)
    vga += 14; // Move to port digits
    for(int i=12; i>=0; i-=4) {
        uint8_t nibble = (port >> i) & 0xF;
        *vga++ = nibble_to_hex(nibble);
        *vga++ = 0x0A;
    }
    
    // Write entropy value (row 3)
    vga = (volatile char*)(VGA_BASE + 320) + 16; // Row 3, column 16
    const char* ent_str = "ENTROPY: ";
    for(int i=0; ent_str[i]; i++) {
        *vga++ = ent_str[i];
        *vga++ = 0x0E; // Yellow text
    }
    
    // Convert entropy to string (xx.xx)
    int ent_int = (int)entropy;
    int ent_frac = (int)((entropy - ent_int) * 100);
    *vga++ = '0' + ent_int / 10;
    *vga++ = 0x0E;
    *vga++ = '0' + ent_int % 10;
    *vga++ = 0x0E;
    *vga++ = '.';
    *vga++ = 0x0E;
    *vga++ = '0' + ent_frac / 10;
    *vga++ = 0x0E;
    *vga++ = '0' + ent_frac % 10;
    *vga++ = 0x0E;
}

double compute_entropy(uint8_t* data, size_t len) {
    if(len == 0) return 0.0;

    int counts[256] = {0};
    for(size_t i=0; i<len; i++) {
        counts[data[i]]++;
    }

    double entropy = 0.0;
    for(int i=0; i<256; i++) {
        if(counts[i] == 0) continue;
        double p = (double)counts[i] / len;
        entropy -= p * log2(p);
    }

    return entropy;
}

void analyze_port(uint16_t port) {
    uint8_t buffer[256];
    
    // Read 256 bytes from port
    for(int i=0; i<256; i++) {
        buffer[i] = inb(port);
    }
    
    double e = compute_entropy(buffer, 256);
    if(e > ENTROPY_THRESHOLD) {
        log_entropy(port, e);
    }
}