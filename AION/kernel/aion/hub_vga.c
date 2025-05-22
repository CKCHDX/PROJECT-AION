#include "hub_vga.h"
#include "vga.h"
#include "../Athena/utils.h"

#define MANUAL_CELL_WIDTH  38
#define MANUAL_CELL_HEIGHT 10

static int g_module_count = 4;
static int g_cols = 2;
static int g_rows = 2;

void hub_vga_init(int module_count) {
    vga_clear();
    g_module_count = module_count;
    // Fixed grid: 2x2 for 4 modules
    g_cols = 2;
    g_rows = 2;

    // Print headers
    for (int i = 0; i < g_module_count; ++i) {
        int col = i % g_cols;
        int row = i / g_cols;
        char header[24];
        switch (i) {
            case 0: athena_snprintf(header, sizeof(header), "MEMORY"); break;
            case 1: athena_snprintf(header, sizeof(header), "LEARNING"); break;
            case 2: athena_snprintf(header, sizeof(header), "PERCEPTION"); break;
            case 3: athena_snprintf(header, sizeof(header), "STEM"); break;
            default: athena_snprintf(header, sizeof(header), "MODULE%d", i); break;
        }
        vga_write_at(header, 0x0E, col * MANUAL_CELL_WIDTH, row * MANUAL_CELL_HEIGHT);
    }
}

void hub_vga_update(int module_idx, int line, const char* str) {
    int col = module_idx % g_cols;
    int row = module_idx / g_cols;
    char buf[MANUAL_CELL_WIDTH + 2];
    int i = 0;
    for (; str[i] && i < MANUAL_CELL_WIDTH - 1; ++i) buf[i] = str[i];
    for (; i < MANUAL_CELL_WIDTH - 1; ++i) buf[i] = ' ';
    buf[MANUAL_CELL_WIDTH - 1] = 0;
    // Write at (col*cell_width, row*cell_height+1+line)
    vga_write_at(buf, 0x0F, col * MANUAL_CELL_WIDTH, row * MANUAL_CELL_HEIGHT + 1 + line);
}
