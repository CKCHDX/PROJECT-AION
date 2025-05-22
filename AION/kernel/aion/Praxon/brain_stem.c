#include "brain_stem.h"
#include "q_learning.h"
#include "action_selection.h"
#include "reward.h"
#include "state.h"
#include "../hub_vga.h"
#include "../Athena/utils.h" // for athena_snprintf

// Internal state
static unsigned int cycles = 0;
static float avg_reward = 0.0f;
static float avg_q_value = 0.0f;
static float max_q_value = 0.0f;
static unsigned int last_report_time = 0;
static unsigned char current_state = 0;
static unsigned char last_action = 0;

// Helper: convert float to int and frac for display
static void float_to_int_frac(float value, int *i, int *f) {
    *i = (int)value;
    *f = (int)(value >= 0 ? (value - *i) * 100.0f : (*i - value) * 100.0f);
    if (*f < 0) *f = -*f;
}

void initialize_brain_stem(void) {
    q_learning_init();
    reward_system_init();
    state_system_init();
    cycles = 0;
    avg_reward = 0.0f;
    avg_q_value = 0.0f;
    max_q_value = 0.0f;
    last_report_time = 0;
    current_state = get_current_state();
    last_action = 0;
}

void update_brain_stem(void) {
    unsigned char new_state = get_current_state();
    float reward = calculate_reward(current_state, last_action, new_state);
    q_learning_update(current_state, last_action, reward, new_state);
    avg_reward = 0.95f * avg_reward + 0.05f * reward;
    cycles++;
    last_action = select_action(new_state);
    apply_action(last_action);
    current_state = new_state;

    unsigned int current_time = get_time_ms();
    if (current_time - last_report_time > HEARTBEAT_INTERVAL || last_report_time == 0) {
        get_learning_metrics(&avg_q_value, &max_q_value);

        // Convert floats to int.frac for display
        int avg_reward_i, avg_reward_f;
        int avg_q_i, avg_q_f;
        int max_q_i, max_q_f;
        float_to_int_frac(avg_reward, &avg_reward_i, &avg_reward_f);
        float_to_int_frac(avg_q_value, &avg_q_i, &avg_q_f);
        float_to_int_frac(max_q_value, &max_q_i, &max_q_f);

        // Compose STEM status string for dashboard
        char stem_status[80];
        athena_snprintf(stem_status, sizeof(stem_status),
            "[STEM] Cyc:%u St:%u Act:%u Gain:%d.%02d Q:%d.%02d MaxQ:%d.%02d",
            cycles, (unsigned int)current_state, (unsigned int)last_action,
            avg_reward_i, avg_reward_f,
            avg_q_i, avg_q_f,
            max_q_i, max_q_f);

        // Output to STEM column in dashboard
        hub_vga_update(HUB_VGA_MODULE_STEM, 0, stem_status);

        last_report_time = current_time;
    }
}
