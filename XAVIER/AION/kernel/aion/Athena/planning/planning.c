#include "planning.h"
#include "../reasoning/reasoning.h"
#include "../hub_vga.h"
#include "../utils.h"

char plan_steps[3][30];
int plan_step_count = 0;

void planning_initialize(void) {
    plan_step_count = 0;
    hub_vga_update(6, 0, "[PLANNING] Initialized");
}

void planning_update(void) {
    int action = reasoning_get_current_action();
    plan_step_count = 0;

    if (action == 1) {
        athena_snprintf(plan_steps[0], sizeof(plan_steps[0]), "Step 1: Gather data");
        athena_snprintf(plan_steps[1], sizeof(plan_steps[1]), "Step 2: Analyze clusters");
        athena_snprintf(plan_steps[2], sizeof(plan_steps[2]), "Step 3: Report findings");
        plan_step_count = 3;
    } else if (action == 2) {
        athena_snprintf(plan_steps[0], sizeof(plan_steps[0]), "Step 1: Focus attention");
        athena_snprintf(plan_steps[1], sizeof(plan_steps[1]), "Step 2: Await input");
        plan_step_count = 2;
    } else {
        athena_snprintf(plan_steps[0], sizeof(plan_steps[0]), "Step 1: Idle");
        plan_step_count = 1;
    }

    hub_vga_update(6, 1, "[PLANNING] Updated");
}

void planning_status(void) {
    for (int i = 0; i < plan_step_count && i < 3; ++i) {
        hub_vga_update(6, 2 + i, plan_steps[i]);
    }
    if (plan_step_count == 0) {
        hub_vga_update(6, 2, "No plan.");
    }
}
