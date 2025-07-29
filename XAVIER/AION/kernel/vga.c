#include "vga.h"
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#define VGA_BUFFER 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile uint16_t* vga = (volatile uint16_t*)VGA_BUFFER;
int cursor_x = 0;
int cursor_y = 0;

static uint8_t current_color = 0x0F;

void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

void vga_hide_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_clear(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga[index] = (current_color << 8) | ' ';
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void vga_set_color(uint8_t color) {
    current_color = color;
}

void vga_write(const char* str) {
    asm volatile ("" ::: "memory");
    while (*str) {
        if (*str == '\b') { // Handle backspace
            if(cursor_x > 0) cursor_x--;
            else if(cursor_y > 0) {
                cursor_y--;
                cursor_x = VGA_WIDTH-1;
            }
            const size_t index = cursor_y * VGA_WIDTH + cursor_x;
            vga[index] = (current_color << 8) | ' ';
        }
        else if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            const size_t index = cursor_y * VGA_WIDTH + cursor_x;
            vga[index] = (current_color << 8) | *str;
            cursor_x++;
        }

        // Handle screen edges
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
        if (cursor_y >= VGA_HEIGHT) {
            cursor_y = 0;
        }

        str++;
    }

    // Update hardware cursor
    uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void itoa(unsigned long num, char* str, int base, int width) {
    char* ptr = str;
    char* start = str;

    // Convert digits (reverse order)
    do {
        unsigned long rem = num % base;
        *ptr++ = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
        num /= base;
    } while (num != 0);

    // Add leading zeros to meet width requirement
    while (ptr - start < width) {
        *ptr++ = '0';
    }

    *ptr-- = '\0';

    // Reverse string to correct order
    while (start < ptr) {
        char tmp = *start;
        *start++ = *ptr;
        *ptr-- = tmp;
    }
}

void vga_write_at(const char* str, uint8_t color, int x, int y) {
    // Boundary checks first!
    if(x >= VGA_WIDTH || y >= VGA_HEIGHT) return;

    uint8_t prev_color = current_color;
    current_color = color;

    for (size_t i = 0; str[i] != '\0' && (x+i) < VGA_WIDTH; i++) {
        const size_t index = y * VGA_WIDTH + x + i;
        vga[index] = (color << 8) | str[i];
    }

    current_color = prev_color;
}
void vga_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buffer[32]; // Reduced buffer size

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            int width = 0;
            // Parse width specifier (e.g., %08X)
            if (*fmt >= '0' && *fmt <= '9') {
                width = *fmt - '0';
                fmt++;
            }
            switch (*fmt) {
                case 'd': {
                    int num = va_arg(args, int);
                    itoa(num, buffer, 10, width);
                    vga_write(buffer);
                    break;
                }
                case 'x': {
                    int num = va_arg(args, int);
                    itoa(num, buffer, 16, width);
                    vga_write(buffer);
                    break;
                }
                case 'l': {
                    fmt++;
                    if (*fmt == 'x') {
                        unsigned long num = va_arg(args, unsigned long);
                        itoa(num, buffer, 16, width);
                        vga_write(buffer);
                    }
                    break;
                }
                default:
                    vga_write("%");
                    char c[2] = {*fmt, 0};
                    vga_write(c);
                    break;
            }
        } else {
            char c[2] = {*fmt, 0};
            vga_write(c);
        }
        fmt++;
    }

    va_end(args);
}


// Print an unsigned integer in decimal
void vga_print_uint(unsigned int value) {
    char buffer[12];
    int i = 0;
    if (value == 0) {
        buffer[i++] = '0';
    } else {
        while (value > 0 && i < 11) {
            buffer[i++] = '0' + (value % 10);
            value /= 10;
        }
    }
    buffer[i] = 0;
    // Reverse and print
    for (int j = i - 1; j >= 0; j--) {
        char c[2] = {buffer[j], 0};
        vga_write(c);
    }
}

// Print a float with specified decimals (simple, not precise, but works for kernel)
void vga_print_float(float value, int decimals) {
    if (value < 0) {
        vga_write("-");
        value = -value;
    }
    unsigned int int_part = (unsigned int)value;
    vga_print_uint(int_part);
    vga_write(".");
    float frac = value - (float)int_part;
    for (int i = 0; i < decimals; i++) {
        frac *= 10;
        int digit = (int)frac;
        vga_print_uint(digit);
        frac -= digit;
    }
}
