#ifndef ATHENA_PERCEPTION_H
#define ATHENA_PERCEPTION_H

#include <stddef.h>
#include <stdint.h>

void perception_initialize(void);
size_t perception_read(uint8_t *buffer, size_t max_size);
void perception_status(void);

#endif // ATHENA_PERCEPTION_H
