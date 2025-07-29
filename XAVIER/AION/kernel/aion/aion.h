#ifndef AION_H
#define AION_H

// Core lifecycle functions
void aion_start(void);
void emergency_shutdown(int reason);

extern unsigned long current_offset;
extern const unsigned long AI_MEMORY_POOL_SIZE;

#endif // AION_H
