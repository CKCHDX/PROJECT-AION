// kernel/aion/core/timer.h
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_tick_handler(void);
void init_pit_timer(uint32_t frequency);

#endif
