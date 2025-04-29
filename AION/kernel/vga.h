#pragma once
#include <stdint.h>

void vga_clear(void);
void vga_hide_cursor(void);
void vga_write(const char* str);
void vga_write_at(const char* str, uint8_t color, int x, int y);
void vga_set_color(uint8_t color);
