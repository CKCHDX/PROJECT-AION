#include "io.h"

void init_serial() {
    outb(0x3F8 + 1, 0x00); // Disable interrupts
    outb(0x3F8 + 3, 0x80); // Enable DLAB
    outb(0x3F8 + 0, 0x03); // Divisor 3 (lo byte)
    outb(0x3F8 + 1, 0x00); //          (hi byte)
    outb(0x3F8 + 3, 0x03); // 8N1
    outb(0x3F8 + 2, 0xC7); // FIFO enabled
}

void serial_putc(char c) {
    while((inb(0x3F8 + 5) & 0x20) == 0);
    outb(0x3F8, c);
}