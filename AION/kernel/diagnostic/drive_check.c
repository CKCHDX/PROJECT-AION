#include "drive_check.h"
#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

int check_drive() {
    outb(0x1F6, 0xA0); // Master drive
    outb(0x1F7, 0xEC); // IDENTIFY command

    uint8_t status = inb(0x1F7);
    if (status == 0x00) return 0; // No device

    while ((status & 0x80) && !(status & 0x08)) {
        status = inb(0x1F7);
    }

    return 1; // Drive is present
}
