#include <string.h>                  // for memcpy
#include "../aion.h"
#include "../io/sensory.h"
#include "../io/effector.h"
#include "../memory/experience.h"
#include "../core/interrupts.h"
#include "reinforcement.h"
#include "../vga.h"          // for vga_clear(), vga_printf()

// Forward-declare the timer tick handler if used in your IRQ0 routine
extern void timer_tick_handler(void);

void ai_lifecycle(void) {
    // ----------------------------------------------------------------------------
    // 1) Initialize neural system
    // ----------------------------------------------------------------------------
    vga_printf("Initializing Neural System...\n");
    neural_init();
    vga_printf("Neural System Initialized\n");

    // ----------------------------------------------------------------------------
    // 2) Interrupts Setup
    // ----------------------------------------------------------------------------
    vga_printf("Initializing Interrupts...\n");
    asm volatile("cli");
    init_interrupts();
    asm volatile("sti");
    vga_printf("Interrupts Initialized\n");

    // ----------------------------------------------------------------------------
    // 3) Main AI Loop
    // ----------------------------------------------------------------------------
    unsigned long cycle = 0;

    while (1) {
        // Efficient CPU Yield
         asm volatile("sti"); // Allow interrupts
         asm volatile("hlt");

        // Process Sensory Input
        vga_printf("Cycle %lu: Processing Sensory Input...\n", cycle);
        process_sensory_input();

        // Create and Store Experience
        struct Experience exp;
        memcpy(exp.state, &sensory_data, sizeof(exp.state));
        exp.action = neural_forward(exp.state);
        exp.reward = calculate_reward();

        // Execute the Chosen Action
        vga_printf("Cycle %lu: Executing Action %u\n", cycle, exp.action);
        execute_action(exp.action);

        // Store Experience
        store_experience(exp);

        // Periodic Learning and Checkpointing
        if (cycle % 10 == 0) {
            vga_printf("Cycle %lu: Updating Q-Learning\n", cycle);
            q_learning_update();
        }

        if (cycle % 1000 == 0) {
            vga_printf("Cycle %lu: Saving Neural State\n", cycle);
            neural_save_state();
        }

        cycle++;
    }
}
void emergency_shutdown(int reason) {
    asm volatile("cli");
    vga_clear();
    vga_printf("EMERGENCY STOP! Reason: 0x%08lX\n", reason); // Use %08lX
    while (1) asm volatile("hlt");
}
void timer_tick_handler() {
    outb(0x20, 0x20); // Acknowledge IRQ0
}