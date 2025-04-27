// In io.c
#include "entropy.h"  // Add this

void blind_io_probe() {
    // Only scan ports 0x0000-0x00FF (safer)
    for(uint16_t port=0x0000; port<0x00FF; port++) {
        analyze_port(port);  // Changed from inb()
    }
}