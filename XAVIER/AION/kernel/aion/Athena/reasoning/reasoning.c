#include "reasoning.h"
#include "../hub_vga.h"
#include "../utils.h"

static ReasoningRule rules[MAX_REASONING_RULES];
static uint8_t current_action = 0;
static uint8_t rule_count = 0;

void reasoning_initialize(void) {
    rules[0] = (ReasoningRule){.condition_id = 1, .action_id = 1};
    rules[1] = (ReasoningRule){.condition_id = 2, .action_id = 2};
    rule_count = 2;
    hub_vga_update(5, 0, "[REASONING] Initialized");
}

void reasoning_update(void) {
    const AttentionState* attention = attention_get_state();
    size_t mem_size;
    const uint8_t* memory = memory_retrieve(&mem_size);

    current_action = 0;
    for (uint8_t i = 0; i < rule_count; i++) {
        switch(rules[i].condition_id) {
            case 1:
                if (mem_size > 5) current_action = rules[i].action_id;
                break;
            case 2:
                if (attention->count > 0 && attention->foci[0].salience > 0.8f)
                    current_action = rules[i].action_id;
                break;
        }
    }
    hub_vga_update(5, 1, "[REASONING] Processed");
}

void reasoning_status(void) {
    char buf[40];
    athena_snprintf(buf, sizeof(buf), "Action: %d", current_action);
    hub_vga_update(5, 2, buf);
}

uint8_t reasoning_get_current_action(void) {
    return current_action;
}
