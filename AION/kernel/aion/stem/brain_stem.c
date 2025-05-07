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

    // Reset VGA state completely
    vga_hide_cursor();
    vga_clear();
    vga_set_color(0x0F); // Bright white on black
    vga_write("=== AION CORE ACTIVATED ===\n\n");

    // Force cursor to start position
    cursor_x = 0;
    cursor_y = 2; // Below header

    while(1) {
        // Save current cursor position
        int saved_x = cursor_x;
        int saved_y = cursor_y;

        // Update status line
        vga_write_at("Security: RUNNING", 0x0A, 0, 24); // Green text on bottom line

        // Main display
        vga_write_at("Cycle ", 0x0F, 0, 3);
        // ... rest of cycle display ...

        // Restore cursor
        cursor_x = saved_x;
        cursor_y = saved_y;

        // Simple delay
        for(int i=0; i<1000000; i++) asm volatile("nop");
    }
}
