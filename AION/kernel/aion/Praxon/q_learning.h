#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <stdint.h>
#define MAX_STATES 16
#define MAX_ACTIONS 4

void q_learning_init(void);
void q_learning_update(uint8_t state, uint8_t action, float reward, uint8_t next_state);
uint8_t get_best_action(uint8_t state);
void get_learning_metrics(float *avg_q, float *max_q);
extern float epsilon;

#endif
