#ifndef ATHENA_PLANNING_H
#define ATHENA_PLANNING_H

void planning_initialize(void);
void planning_update(void);
void planning_status(void);

// Expose for action.c
extern char plan_steps[3][30];
extern int plan_step_count;

#endif
