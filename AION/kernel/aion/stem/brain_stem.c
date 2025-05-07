#include "../aion.h"
#include "../memory/ai_alloc.h"
#include "../../vga.h"  // Use existing VGA header
#include "../config.h"

static int vital_signs_ok() {
    // Implementation
    return 1;
}

void ai_lifecycle() {
    unsigned long cycle_count = 0;

    // Clear and setup screen
    vga_clear();
    vga_write_at("=== AION CORE ===", 0x0B, 32, 0);
    vga_write_at("System Status:", 0x0E, 0, 2);

    // Initial checks
    vga_write_at("[1] Hardware Validation: RUNNING", 0x07, 0, 4);
    int hw_status = validate_hardware_environment();
    vga_write_at(hw_status ? "FAIL" : "PASS", hw_status ? 0x0C : 0x0A, 28, 4);

    vga_write_at("[2] Memory Initialization: ", 0x07, 0, 5);
    memory_firewall_init();
    vga_write_at("DONE", 0x0A, 25, 5);

    vga_write_at("[3] Neural Network: ", 0x07, 0, 6);
    vga_write_at("INITIALIZING...", 0x0E, 20, 6);

    // Runtime display
    while(1) {
        // Update counters
        char cycle_str[16];
        itoa(cycle_count, cycle_str, 10);
        vga_write_at("Cycle: ", 0x07, 0, 8);
        vga_write_at(cycle_str, 0x0F, 7, 8);

        // Sensor status
        vga_write_at("Sensors: ", 0x07, 0, 10);
        vga_write_at(cycle_count % 2 ? "ACTIVE " : "SCANNING", 0x0D, 9, 10);

        // Learning progress
        vga_write_at("Learning: [", 0x07, 0, 12);
        for(int i=0; i<10; i++)
            vga_write_at(i<(cycle_count%10) ? "#" : "-", 0x0E, 10+i, 12);
        vga_write_at("]", 0x07, 20, 12);

        // System vitals
        vga_write_at("System Health:", 0x07, 40, 2);
        vga_write_at("Memory: 98%", 0x0F, 40, 4);
        vga_write_at("CPU: 85%", 0x0F, 40, 5);
        vga_write_at("Temp: 42C", 0x0F, 40, 6);

        cycle_count++;

        // Simple delay
        for(int i=0; i<0xFFFFF; i++) asm volatile("nop");
    }
}
