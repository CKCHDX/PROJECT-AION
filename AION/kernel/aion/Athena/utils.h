#ifndef ATHENA_UTILS_H
#define ATHENA_UTILS_H

#include <stddef.h>
#include <stdint.h>

// Minimal memcpy
void *athena_memcpy(void *dest, const void *src, size_t n);

// Minimal strlen
size_t athena_strlen(const char *s);

// Print string using kernel VGA output
void athena_print(const char *msg);

#endif // ATHENA_UTILS_H
