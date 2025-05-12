#pragma once

void idt_init(void);
void idt_set_gate(int num, unsigned long base, unsigned short sel, unsigned char flags);

struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));