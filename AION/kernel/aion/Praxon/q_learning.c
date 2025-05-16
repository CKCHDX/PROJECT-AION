#include "q_learning.h"

static float q_table[MAX_STATES][MAX_ACTIONS];
float epsilon = 0.2f;
static float learning_rate = 0.1f;
static float discount_factor = 0.95f;

void q_learning_init(void) {
    for (int s = 0; s < MAX_STATES; ++s)
        for (int a = 0; a < MAX_ACTIONS; ++a)
            q_table[s][a] = 0.0f;
}

void q_learning_update(uint8_t state, uint8_t action, float reward, uint8_t next_state) {
    float max_next = q_table[next_state][0];
    for (int a = 1; a < MAX_ACTIONS; ++a)
        if (q_table[next_state][a] > max_next)
            max_next = q_table[next_state][a];
    float td = reward + discount_factor * max_next - q_table[state][action];
    q_table[state][action] += learning_rate * td;
}

uint8_t get_best_action(uint8_t state) {
    float max_q = q_table[state][0];
    uint8_t best = 0;
    for (int a = 1; a < MAX_ACTIONS; ++a)
        if (q_table[state][a] > max_q) {
            max_q = q_table[state][a];
            best = a;
        }
        return best;
}

void get_learning_metrics(float *avg_q, float *max_q) {
    float sum = 0.0f, maxv = q_table[0][0];
    int count = 0;
    for (int s = 0; s < MAX_STATES; ++s)
        for (int a = 0; a < MAX_ACTIONS; ++a) {
            float v = q_table[s][a];
            sum += v;
            if (v > maxv) maxv = v;
            count++;
        }
        *avg_q = sum / count;
    *max_q = maxv;
}
