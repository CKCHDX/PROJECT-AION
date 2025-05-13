// kernel/aion/io/sensory.c
#include "sensory.h"
#include "../security/permissions.h"
#include "../brain/prng.h"

struct SensoryData sensory_data;

void init_sensors() {
    asm volatile("cli");
    outb(0xE2, 0x1);
    outb(0xE4, 0x1);
    asm volatile("sti");
}

void process_sensory_input(void) {
    static uint32_t last_total = 0, last_idle = 0;
    uint32_t temp, total_low, total_high, idle;

    // Read CPU temperature
    asm volatile("mov $0x1A2, %%ecx; rdmsr" : "=a"(temp));
    sensory_data.temperature = (temp >> 16) & 0x7F;

    // Read CPU load
    asm volatile("rdtsc" : "=a"(total_low), "=d"(total_high));
    asm volatile("inb $0xE4, %%al" : "=a"(idle));
    
    uint32_t total = total_low;
    uint32_t diff_total = total - last_total;
    uint32_t diff_idle = idle - last_idle;
    
    sensory_data.cpu_load = diff_total ? 
        (100 - (diff_idle * 100) / diff_total) : 0;

    last_total = total;
    last_idle = idle;

    // Add timestamp using PRNG-based entropy
    sensory_data.timestamp = xorshift32();
}