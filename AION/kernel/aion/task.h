#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define TASK_READY 0
#define TASK_RUNNING 1

typedef struct task {
    uint32_t id;
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    uint32_t* stack;
    int state;
    struct task* next;
} task_t;

void create_task(void (*entry_point)());
void run_next_task();
void task_yield();

#endif
