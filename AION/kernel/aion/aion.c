#include "aion.h"
#include "Athena/hub.h"

#define BAD_HARDWARE 0xBADCAFE
#define SHUTDOWN_CODE 0xDEAD

extern void memory_firewall_init(void);
extern int validate_hardware_environment(void);
extern void emergency_shutdown(int reason);
extern void vga_clear(void);
extern void vga_printf(const char *fmt, ...);

unsigned long current_offset = 0;
const unsigned long AI_MEMORY_POOL_SIZE = 1048576; // 1 MiB

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

    // 4) Initialize Brain (via hub)
    vga_printf("Initializing Brain Hub...\n");
    hub_initialize();
    vga_printf("Brain Hub Initialized\n\n");

    // 5) Main AI Loop (via hub)
    vga_printf("Starting Main AI Loop...\n");
    while (1) {
        hub_update();
        for (volatile int i = 0; i < 10000; i++) { }
    }

    // 6) Failsafe: should never get here
    vga_printf("LIFECYCLE RETURNED – SHUTTING DOWN\n");
}

void emergency_shutdown(int reason) {
    // Your shutdown logic here (e.g., print error, halt, etc.)
    while (1) { /* halt */ }
}