#ifndef HUB_VGA_H
#define HUB_VGA_H

// Call once at boot, pass number of modules to display
void hub_vga_init(int module_count);
void hub_vga_update(int module_idx, int line, const char* str);

// Module indices for clarity
#define HUB_VGA_MODULE_MEMORY     0
#define HUB_VGA_MODULE_LEARNING   1
#define HUB_VGA_MODULE_PERCEPTION 2
#define HUB_VGA_MODULE_STEM       3
#define HUB_VGA_MODULE_ATTENTION  4

// VGA dimensions
#define VGA_WIDTH 90
#define VGA_HEIGHT 50

#endif // HUB_VGA_H
