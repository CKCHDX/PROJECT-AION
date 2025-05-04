#include "../vga.h"
#include "scheduler.h"
#include "task.h"

void switch_task();

void init_scheduler() {
    vga_write("[*] Starting task scheduler...\n");
    // Placeholder for round-robin or cooperative scheduling
}
