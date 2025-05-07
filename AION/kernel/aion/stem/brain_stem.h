#ifndef BRAIN_STEM_H
#define BRAIN_STEM_H

#define HEARTBEAT_INTERVAL 100  // ms

void initialize_brain_stem();
void ai_lifecycle();
void emergency_shutdown(int reason);

#endif
