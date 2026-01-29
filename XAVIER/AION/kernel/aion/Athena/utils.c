// Athena/utils.c

#include "utils.h"
#include <stdarg.h>
#include <stdint.h>

// Simple memcpy
void *athena_memcpy(void *dest, const void *src, size_t n)
{
    uint8_t *d = (uint8_t*)dest;
    uint8_t *s = (uint8_t*)src;
    for (size_t i = 0; i < n; ++i)
        d[i] = s[i];
    return dest;
}

// Simple memset
void *athena_memset(void *dest, int val, size_t n)
{
    uint8_t *d = (uint8_t*)dest;
    uint8_t v = (uint8_t)val;
    for (size_t i = 0; i < n; ++i)
        d[i] = v;
    return dest;
}

// String length
size_t athena_strlen(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
        ++len;
    return len;
}

// Print to VGA
void athena_print(const char *msg)
{
    extern void vga_printf(const char *fmt, ...);
    vga_printf("%s", msg);
}

// Minimal snprintf: supports %d, %x, %02x, %s
int athena_snprintf(char *buf, size_t size, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char *p      = buf;
    size_t left  = (size > 0) ? size - 1 : 0;

    while (*fmt && left)
    {
        if (*fmt == '%')
        {
            ++fmt;
            int pad2hex = 0;

            // detect "%02x"
            if (*fmt == '0' && fmt[1] == '2' && fmt[2] == 'x')
            {
                pad2hex = 1;
                fmt += 2;
            }

            char tmp[32];
            int  len = 0;

            switch (*fmt)
            {
                case 'd': {
                    int val = va_arg(args, int);
                    if (val == 0)
                    {
                        tmp[len++] = '0';
                    }
                    else
                    {
                        int  v    = (val < 0) ? -val : val;
                        while (v > 0 && len < (int)sizeof(tmp)-1)
                        {
                            tmp[len++] = '0' + (v % 10);
                            v /= 10;
                        }
                        if (val < 0)
                            tmp[len++] = '-';
                    }
                    // reverse
                    for (int i = len - 1; i >= 0 && left; --i, --left)
                        *p++ = tmp[i];
                    break;
                }

                case 'x': {
                    int val = va_arg(args, int);
                    if (pad2hex)
                    {
                        // always two hex digits
                        *p++ = "0123456789abcdef"[(val >> 4) & 0xF];
                        if (--left == 0) break;
                        *p++ = "0123456789abcdef"[ val       & 0xF];
                        --left;
                    }
                    else
                    {
                        // trim leading zeros
                        int started = 0;
                        for (int b = 28; b >= 0; b -= 4)
                        {
                            int nibble = (val >> b) & 0xF;
                            if (nibble || started || b == 0)
                            {
                                started = 1;
                                if (left) { *p++ = "0123456789abcdef"[nibble]; --left; }
                            }
                        }
                    }
                    break;
                }

                case 's': {
                    const char *s = va_arg(args, const char*);
                    while (*s && left)
                    {
                        *p++ = *s++;
                        --left;
                    }
                    break;
                }

                default:
                    // Unknown specifier, emit literally
                    if (left) { *p++ = '%'; --left; }
                    if (left) { *p++ = *fmt; --left; }
                    break;
            }
        }
        else
        {
            *p++ = *fmt;
            --left;
        }
        ++fmt;
    }

    *p = '\0';
    va_end(args);
    return (int)(p - buf);
}
