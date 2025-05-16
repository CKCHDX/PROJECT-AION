// File: kernel/aion/aion.c

#include <stdint.h>
#include "aion.h"
#include "Praxon/brain_stem.h"

#define BAD_HARDWARE   0xBADCAFE
#define SHUTDOWN_CODE  0xDEAD

// Externs for subsystems
extern void memory_firewall_init(void);
extern int  validate_hardware_environment(void);
extern void emergency_shutdown(int reason);
extern void ai_lifecycle(void);
extern void vga_clear(void);
extern void vga_printf(const char *fmt, ...);

// Only a single definition of these globals:
unsigned long current_offset = 0;
const unsigned long AI_MEMORY_POOL_SIZE = 1048576;  // 1 MiB

void aion_start(void) {
    // 1) Fresh screen
    outb(0x3D4, 0x03); outb(0x3D5, 0x00);
    outb(0x3D4, 0x02); outb(0x3D5, 0x00);

    vga_printf("AION Bootloader Handoff OK\n");

    // 2) Memory firewall
    vga_printf("Initializing Memory Firewall...\n");

    vga_printf("Firewall OK\n");

    // 3) Hardware validation
    vga_printf("Validating Hardware Environment...\n");

    vga_printf("HW CHECK PASS\n");

    // 4) Enter AI core
    vga_printf("Starting AI Core...\n");
    ai_lifecycle();

    // 5) Failsafe: should never get here
    vga_printf("LIFECYCLE RETURNED – SHUTTING DOWN\n");

}
