#include "utils.h"

// Use your kernel's VGA print function
extern void vga_printf(const char *fmt, ...);

void *athena_memcpy(void *dest, const void *src, size_t n) {
    uint8_t *d = (uint8_t*)dest;
    const uint8_t *s = (const uint8_t*)src;
    for (size_t i = 0; i < n; ++i) d[i] = s[i];
    return dest;
}

size_t athena_strlen(const char *s) {
    size_t len = 0;
    while (s[len]) ++len;
    return len;
}

void athena_print(const char *msg) {
    vga_printf("%s", msg);
}
