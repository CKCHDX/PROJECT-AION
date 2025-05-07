#ifndef AION_VGA_H
#define AION_VGA_H

void vga_clear_screen(char color);
void vga_printf(const char* fmt, ...);
void vga_putchar(char c);
void emergency_shutdown(int reason);

#endif
