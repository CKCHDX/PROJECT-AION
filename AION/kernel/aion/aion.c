#include <stdint.h>
#include "aion.h"
#include "stem/brain_stem.h"

#define BAD_HARDWARE 0xBADCAFE
#define SHUTDOWN_CODE 0xDEAD

void aion_start(void) {
    // Immediate screen test
    volatile uint16_t* vga = (volatile uint16_t*)0xB8000;
    vga[0] = 0x0F00 | 'S'; // Should see 'S' top-left

    memory_firewall_init();
    vga[1] = 0x0F00 | 'T'; // 'ST' = passed firewall

    if (validate_hardware_environment() != 0) {
        vga[2] = 0x0F00 | 'X'; // 'STX' = hardware failed
        emergency_shutdown(BAD_HARDWARE);
    }

    vga[2] = 0x0F00 | 'A'; // 'STA' = all checks passed

    ai_lifecycle();
    emergency_shutdown(SHUTDOWN_CODE);
}
