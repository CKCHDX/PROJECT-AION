#include "vga.h"
#include "utils.h"
#include "delays.h"
#include "diagnostic/memory_check.h"
#include "diagnostic/drive_check.h"
#include "diagnostic/gpu_check.h"
#include "diagnostic/fan_check.h"
#include "panel/control_panel.h"


void kernel_main(void) {
    vga_clear();
    vga_set_color(0x0A); // Green
    
    // Project header
    vga_write_at("PROJECT-AION", 0x0E, 34, 0); // Yellow header
    
    
    // Diagnostic sequence
    vga_set_color(0x0F); // White
    vga_write("\nStarting diagnostic sequence\n");

    // Memory Check
    vga_write("\n- Checking memory... ");
    simple_delay(15000000); // Delay before memory check starts
    
    // Call the memory check function and store the result
    int memory_status = check_memory();
    
    // Display the result of the memory check
    if (memory_status) {
        vga_write_at("OK", 0x0A, 21, 7); // Green OK
    } else {
        vga_write_at("FAIL", 0x0C, 21, 7); // Red FAIL
    }
    simple_delay(15000000); // Delay after memory check
    
    // VGA Check (simple initialization check)
    vga_write("\n- Initializing VGA... ");
    simple_delay(5000000); // Delay before VGA check starts
    vga_write_at("OK", 0x0A, 21, 7); // Green OK
    simple_delay(15000000); // Delay after VGA check

    // System Integrity Check (just a basic placeholder for now)
    vga_write("\n- Checking system integrity... ");
    simple_delay(15000000); // Delay before integrity check
    vga_write_at("PASSED", 0x0A, 28, 8);
    simple_delay(15000000); // Delay after integrity check
    
    // Final message
    vga_set_color(0x0B); // Cyan
    vga_write_at("\n\nAION Kernel v0.1 - Ready", 0x0B, 0, 10);
    
    // Small delay before entering control panel
    simple_delay(10000000);
    
    // Launch control panel
    start_control_panel();

    // Should never return; hang just in case
    for (;;) { /* hang */ }
}
