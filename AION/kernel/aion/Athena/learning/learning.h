#ifndef ATHENA_LEARNING_H
#define ATHENA_LEARNING_H

#include <stddef.h>
#include <stdint.h>

#define MAX_CLUSTERS 8

void learning_initialize(void);
void learning_process(void);
void learning_status(void);

#endif // ATHENA_LEARNING_H
