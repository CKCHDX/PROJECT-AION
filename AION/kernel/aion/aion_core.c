#include "../vga.h"
#include "memory_map.h"
#include "scheduler.h"
#include "memory_manager.h"   // Ensure this is included here
#include "task.h"  // Include the task header for the function prototypes

// Function prototypes
void task1(void);
void task2(void);
void create_task(void (*entry_point)());
void run_next_task();
void task_yield();

void aion_start() {
    vga_clear();
    vga_set_color(0x0B);
    vga_write(">>> AION Core Booting...\n");

    init_memory_map();
    init_memory_manager();   // Initialize the memory manager
    init_scheduler();
    create_task(task1);
    create_task(task2);

    // Start running the first task manually
    run_next_task();

    vga_write("[*] Preparing AION environment...\n");
    vga_write("\nAION is now running.\n");

    // Example of memory allocation:
    char *ptr = alloc_memory(512);   // Request 512 bytes
    if (ptr) {
        vga_write("[*] Memory allocated successfully!\n");
    } else {
        vga_write("[*] Memory allocation failed.\n");
    }

    while (1) {}  // Hang for now
}

void task1() {
    while (1) {
        vga_write("[Task 1] Running...\n");
        for (int i = 0; i < 1000000; i++);
        task_yield();
    }
}

void task2() {
    while (1) {
        vga_write("[Task 2] Running...\n");
        for (int i = 0; i < 1000000; i++);
        task_yield();
    }
}
