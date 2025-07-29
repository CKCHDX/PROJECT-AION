#ifndef HUB_VGA_H
#define HUB_VGA_H

void hub_vga_init(int module_count);
void hub_vga_update(int module_idx, int line, const char* str);

#define HUB_VGA_MODULE_MEMORY     0
#define HUB_VGA_MODULE_LEARNING   1
#define HUB_VGA_MODULE_PERCEPTION 2
#define HUB_VGA_MODULE_STEM       3
#define HUB_VGA_MODULE_ATTENTION  4
#define HUB_VGA_MODULE_REASONING  5
#define HUB_VGA_MODULE_PLANNING 6
#define HUB_VGA_MODULE_ACTION 7

#define VGA_WIDTH 90
#define VGA_HEIGHT 50

#endif // HUB_VGA_H
