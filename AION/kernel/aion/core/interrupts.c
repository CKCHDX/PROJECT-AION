#include "interrupts.h"
#include "../io/io.h"
#include <stdint.h>

// Define the PIT input frequency (1193180 Hz)
#define PIT_INPUT_FREQ 1193180

// Declare the external ISR functions from the assembly file
extern void _isr0(void);
extern void _isr14(void);
extern void _irq0_handler(void);

// These symbols come from your interrupts.S:
extern void load_idt(void);

// Define the IDT and its descriptor
#define IDT_ENTRIES 256
struct idt_entry idt[IDT_ENTRIES];

void idt_init(void) {
    // Set the IDT gates for specific interrupts
    set_idt_gate(0, (unsigned)_isr0, 0x08, 0x8E);  // Divide Error
    set_idt_gate(14, (unsigned)_isr14, 0x08, 0x8E); // Page Fault
    // ... other entries ...
}

// Remap the Master (0x20) and Slave (0xA0) PICs to vectors 0x20–0x2F
static void pic_remap(void) {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}

// Initialize the Programmable Interval Timer to the given frequency (Hz)
static void pit_init(int hz) {
    uint16_t divisor = (uint16_t)(PIT_INPUT_FREQ / hz);  // Using PIT_INPUT_FREQ here
    outb(0x43, 0x36);  // Command to PIT for setting frequency
    outb(0x40, (uint8_t)(divisor & 0xFF));  // Low byte of divisor
    outb(0x40, (uint8_t)(divisor >> 8));  // High byte of divisor
}

// Set an IDT entry
void set_idt_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
}

// Initialize the IDT and the PIC
void init_interrupts(void) {
    // Clear the IDT entries
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt[i].base_lo = 0;
        idt[i].base_hi = 0;
        idt[i].sel = 0;
        idt[i].always0 = 0;
        idt[i].flags = 0;
    }

    // PIC remapping
    pic_remap();

    // Set the IRQ0 handler (PIT)
    set_idt_gate(32, (uint32_t)_irq0_handler, 0x08, 0x8E);

    // Load the IDT
    load_idt();

    // Initialize PIT at 100 Hz for regular timer ticks
    pit_init(100);

    // Enable CPU interrupts
    asm volatile("sti");
}

void handle_interrupts(void) {
    outb(0x20, 0x20); // Send EOI to PIC
}
