#ifndef STATE_H
#define STATE_H

void state_system_init(void);
unsigned char get_current_state(void);
void apply_action(unsigned char action);
unsigned int get_time_ms(void);
void print_status(unsigned int cycles, unsigned char state, unsigned char action, float avg_reward, float avg_q, float max_q);

#endif
