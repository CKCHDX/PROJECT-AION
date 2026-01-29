#ifndef ATHENA_UTILS_H
#define ATHENA_UTILS_H

#include <stddef.h>
#include <stdint.h>

void *athena_memcpy(void *dest, const void *src, size_t n);
void *athena_memset(void *dest, int val, size_t n);
size_t athena_strlen(const char *s);
void athena_print(const char *msg);

// Minimal snprintf for integers and hex (kernel-safe)
int athena_snprintf(char *buf, size_t size, const char *fmt, ...);

#endif // ATHENA_UTILS_H
