#include "state.h"
#include "../vga.h"  // Use your own VGA/kdebug output function
#include <stdio.h>
// Internal simulated state and timer
static unsigned char sim_state = 0;
static unsigned int sim_time = 0;

// Initialize the simulated state and time
void state_system_init(void) {
    sim_state = 0;
    sim_time = 0;
}

// Return the current simulated state
unsigned char get_current_state(void) {
    return sim_state;
}

// Apply an action to the simulated state
void apply_action(unsigned char action) {
    // Simple: state increments by action value, wraps at 16
    sim_state = (sim_state + action) % 16;
    sim_time += 10; // Simulate time passing
}

// Return the simulated time in ms
unsigned int get_time_ms(void) {
    return sim_time;
}

// Print status using your VGA output function (not printf)
void print_status(unsigned int cycles, unsigned char state, unsigned char action, float avg_reward, float avg_q, float max_q) {
    // Print each value in sequence, since vga_printf may not support floats or all format specifiers
    vga_printf("[STEM] Cycles: ");
    vga_print_uint(cycles);
    vga_printf(" | State: ");
    vga_print_uint(state);
    vga_printf(" | Action: ");
    vga_print_uint(action);
    vga_printf(" | Gain: ");
    vga_print_float(avg_reward, 4);
    vga_printf(" | Avg Q: ");
    vga_print_float(avg_q, 4);
    vga_printf(" | Max Q: ");
    vga_print_float(max_q, 4);
    vga_printf("\n");
}
