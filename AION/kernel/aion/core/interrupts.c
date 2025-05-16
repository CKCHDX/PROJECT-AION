#include "interrupts.h"
#include "../io/io.h"
#include <stdint.h>

// Define the PIT input frequency (1193180 Hz)
#define PIT_INPUT_FREQ 1193180

// Declare the external ISR functions from the assembly file
extern void _isr0(void);
extern void _isr14(void);
extern void _irq0_handler(void);
extern void _isr_default(void);
extern void timer_tick_handler(void);

// Define the IDT and its pointer
struct idt_entry idt[256] __attribute__((aligned(16)));
struct idt_ptr idt_ptr;

// These symbols come from your interrupts.S:
extern void load_idt(void);

// Set an IDT entry
void set_idt_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
}

// Initialize the IDT entries
void idt_init(void) {
    // Setup the IDT pointer
    idt_ptr.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt;

    // Initialize all IDT entries to the default handler
    for (int i = 0; i < 256; i++) {
        set_idt_gate(i, (uint32_t)_isr_default, 0x08, 0x8E);
    }

    // Set specific handlers for important interrupts
    set_idt_gate(0, (uint32_t)_isr0, 0x08, 0x8E);  // Divide Error
    set_idt_gate(14, (uint32_t)_isr14, 0x08, 0x8E); // Page Fault

    // Set IRQ handlers (after remapping, IRQ0 is at interrupt 32)
    set_idt_gate(32, (uint32_t)_irq0_handler, 0x08, 0x8E); // IRQ0 - PIT
}

// Remap the Master (0x20) and Slave (0xA0) PICs to vectors 0x20–0x2F
static void pic_remap(void) {
    // ICW1: Initialize PIC
    outb(0x20, 0x11); // Master PIC
    outb(0xA0, 0x11); // Slave PIC

    // ICW2: Vector offset
    outb(0x21, 0x20); // Master offset (IRQ0-7 -> INT 0x20-0x27)
    outb(0xA1, 0x28); // Slave offset (IRQ8-15 -> INT 0x28-0x2F)

    // ICW3: Master/Slave wiring
    outb(0x21, 0x04); // Tell Master that Slave is at IRQ2
    outb(0xA1, 0x02); // Tell Slave its ID is 2

    // ICW4: Set mode
    outb(0x21, 0x01); // 8086 mode
    outb(0xA1, 0x01); // 8086 mode

    // Mask all interrupts except IRQ0 (timer)
    outb(0x21, 0xFE); // Enable only IRQ0
    outb(0xA1, 0xFF); // Disable all IRQs on slave PIC
}

// Initialize the Programmable Interval Timer to the given frequency (Hz)
static void pit_init(int hz) {
    uint16_t divisor = (uint16_t)(PIT_INPUT_FREQ / hz);

    // Command to PIT: channel 0, access mode lobyte/hibyte, mode 3 (square wave)
    outb(0x43, 0x36);

    // Send divisor
    outb(0x40, (uint8_t)(divisor & 0xFF));  // Low byte of divisor
    outb(0x40, (uint8_t)(divisor >> 8));    // High byte of divisor
}

// Initialize the IDT and the PIC
void init_interrupts(void) {
    // Initialize IDT entries
    idt_init();

    // Remap PIC before loading the IDT to avoid spurious interrupts
    pic_remap();

    // Load the IDT
    load_idt();

    // Initialize PIT at 100 Hz for regular timer ticks
    pit_init(100);
}
