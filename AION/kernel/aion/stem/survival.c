#include "../aion.h"

void emergency_shutdown(int reason) {
    // Save state if possible
    asm volatile ("cli");
    asm volatile ("hlt");
}
