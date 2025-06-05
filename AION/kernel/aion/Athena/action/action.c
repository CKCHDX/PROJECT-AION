#include "action.h"
#include "../planning/planning.h"
#include "../hub_vga.h"
#include "../utils.h"

static char current_action[30] = "None";
static int action_progress = 0;

void action_initialize(void) {
    current_action[0] = '\0';
    action_progress = 0;
    hub_vga_update(7, 0, "[ACTION] Initialized");
}

void action_execute(void) {
    // Use plan_steps/plan_step_count from planning
    if (plan_step_count > 0) {
        athena_snprintf(current_action, sizeof(current_action), "Executing: %s", plan_steps[0]);
        action_progress = 33; // Simulate progress
    } else {
        athena_snprintf(current_action, sizeof(current_action), "No action");
        action_progress = 0;
    }
    hub_vga_update(7, 1, "[ACTION] Updated");
}

void action_status(void) {
    char buf[30];
    athena_snprintf(buf, sizeof(buf), "%s", current_action);
    hub_vga_update(7, 2, buf);

    athena_snprintf(buf, sizeof(buf), "Progress: %d%%", action_progress);
    hub_vga_update(7, 3, buf);
}
