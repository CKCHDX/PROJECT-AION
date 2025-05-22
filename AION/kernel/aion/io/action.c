// kernel/aion/io/action.c

#include "action.h"
#include "../io/sensory.h"        // for init_sensors()
#include "../memory/state_save.h" // for neural_save_state()
#include "../vga.h"       // for vga_printf()

void execute_action(int action_id) {
    switch (action_id) {
        case ACTION_SAVE_STATE:
            neural_save_state();
            break;

        case ACTION_RESET_SENSORS:
            init_sensors();
            break;

        default:
            // Report invalid action instead of triggering hardware reset
            vga_printf("Invalid action ID: 0x%02X\n", (unsigned)action_id);
            break;
    }
}
