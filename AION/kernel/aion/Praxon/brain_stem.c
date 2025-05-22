#include "brain_stem.h"
#include "q_learning.h"
#include "action_selection.h"
#include "reward.h"
#include "state.h"

// Internal state
static unsigned int cycles = 0;
static float avg_reward = 0.0f;
static float avg_q_value = 0.0f;
static float max_q_value = 0.0f;
static unsigned int last_report_time = 0;
static unsigned char current_state = 0;
static unsigned char last_action = 0;

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
        print_status(cycles, current_state, last_action, avg_reward, avg_q_value, max_q_value);
        last_report_time = current_time;
    }
}
