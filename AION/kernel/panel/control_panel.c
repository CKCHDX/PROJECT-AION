#include "vga.h"
#include "utils.h"
#include "input.h"

#include "hardware_check.h"  // Add this
#include "aion_check.h"      // Add this
#include "reset.h"           // Add this
#include "boot.h"

void start_control_panel() {
    vga_clear();
    vga_set_color(0x0E); // Yellow header
    vga_write_at("=== AION CONTROL PANEL ===", 0x0E, 25, 0);
    simple_delay(15000000); // Add delay after printing

    vga_set_color(0x0F); // White
    vga_write("\n\n[1] Running system diagnostics...\n");
    simple_delay(15000000); // Add delay after printing

    if (!run_hardware_checks()) {
        vga_set_color(0x0C);
        vga_write("!! Hardware check failed !!\n");
        simple_delay(15000000); // Add delay after printing
        for (;;) {} // Hang
    }

    vga_write("[2] Verifying AION runtime...\n");
    simple_delay(15000000); // Add delay after printing

    if (!verify_aion()) {
        vga_set_color(0x0C);
        vga_write("!! AION integrity check failed !!\n");
        simple_delay(15000000); // Add delay after printing
        for (;;) {}
    }

    vga_set_color(0x0A); // Green
    vga_write("\nSystem OK.\n");
    simple_delay(15000000); // Add delay after printing

    vga_set_color(0x0F);
    vga_write("Press ENTER to start AION.\n");
    simple_delay(15000000); // Add delay after printing
    vga_write("Press R to RESET AION.\n");
    simple_delay(15000000); // Add delay after printing

    char key = wait_for_keypress();

    if (key == 'r') {
        vga_write("\n!!! RESETTING AION !!!\n");
        simple_delay(15000000); // Add delay after printing
        reset_aion_memory(); // Placeholder: implement memory wipe
        reboot();            // Placeholder: implement system restart
    }

    if (key == '\n') {
        vga_write("\n>>> BOOTING AION <<<\n");
        simple_delay(15000000); // Add delay after printing
        boot_aion();         // Placeholder: jump to AION main kernel
    }

    for (;;) {} // Hang if none triggered
}
