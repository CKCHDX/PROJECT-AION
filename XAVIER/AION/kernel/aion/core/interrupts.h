#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

// IDT Entry Structure
struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
} __attribute__((packed));

// IDT Pointer Structure
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void init_interrupts(void);
void set_idt_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);

#endif
