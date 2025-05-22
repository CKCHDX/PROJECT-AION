// kernel/aion/core/timer.c
#include "timer.h"
#include "../io/sensory.h"
#include "interrupts.h"
#include <stdint.h>

#define PIT_BASE_FREQ 1193180

void init_pit_timer(uint32_t freq) {
    uint16_t divisor = (uint16_t)(PIT_BASE_FREQ / freq);

    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

void timer_tick_handler(void) {
    static uint32_t ticks = 0;
    ticks++;

    // Update sensors every second (assuming 1000Hz timer)
    if(ticks % 1000 == 0) {
        process_sensory_input();
    }

    outb(0x20, 0x20);  // EOI
}
