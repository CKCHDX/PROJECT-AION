// kernel/aion/io/sensory.h
#ifndef SENSORY_H
#define SENSORY_H

#include <stdint.h>

struct SensoryData {
    float temperature;
    float memory_usage;
    float cpu_load;
    uint32_t timestamp;
};

extern struct SensoryData sensory_data;

void init_sensors(void);
void process_sensory_input(void);

#endif