// kernel/aion/io/action.h
#ifndef ACTION_H
#define ACTION_H

// Action ID definitions
#define ACTION_SAVE_STATE     0x01
#define ACTION_RESET_SENSORS  0x02
#define ACTION_HARD_RESET     0xFF

void execute_action(int action_id);

#endif