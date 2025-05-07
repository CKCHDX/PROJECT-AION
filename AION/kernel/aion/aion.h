#ifndef AION_H
#define AION_H

// Core lifecycle functions
void aion_start(void);
void emergency_shutdown(int reason);

// Brain stem functions
void process_sensory_input(void);
void run_learning_cycle(void);
void execute_actions(void);

// Learning system
float get_prediction(void);
float get_outcome(void);
void adjust_weights(float error);
// In aion.h
void emergency_shutdown(int reason);
// Security functions (add these)
void memory_firewall_init(void);
int validate_hardware_environment(void);

#endif
