#include "hub_vga.h"
#include "vga.h"
#include "../Athena/utils.h"

// Adjusted cell dimensions for better fit
#define MANUAL_CELL_WIDTH  26
#define MANUAL_CELL_HEIGHT 8

static int g_module_count = 7; // Default to 5
static int g_cols = 3;
static int g_rows = 2;


void hub_vga_init(int module_count) {
    vga_clear();
    g_module_count = module_count;

    // Determine grid layout
    if (module_count <= 7) {
        g_cols = 3;
        g_rows = 2;
    } else {
        g_cols = 3;
        g_rows = 2;
    }

    // Print headers
    for (int i = 0; i < g_module_count; ++i) {
        int col = i % g_cols;
        int row = i / g_cols;
        char header[24];
        switch (i) {
            case HUB_VGA_MODULE_MEMORY:     athena_snprintf(header, sizeof(header), "MEMORY"); break;
            case HUB_VGA_MODULE_LEARNING:   athena_snprintf(header, sizeof(header), "LEARNING"); break;
            case HUB_VGA_MODULE_PERCEPTION: athena_snprintf(header, sizeof(header), "PERCEPTION"); break;
            case HUB_VGA_MODULE_STEM:       athena_snprintf(header, sizeof(header), "STEM"); break;
            case HUB_VGA_MODULE_ATTENTION:  athena_snprintf(header, sizeof(header), "ATTENTION"); break;
            case HUB_VGA_MODULE_REASONING:  athena_snprintf(header, sizeof(header), "REASONING"); break;
	    case HUB_VGA_MODULE_PLANNING: athena_snprintf(header, sizeof(header), "PLANNING"); break;
	    case HUB_VGA_MODULE_ACTION:    athena_snprintf(header, sizeof(header), "ACTION"); break;
            default: athena_snprintf(header, sizeof(header), "MODULE%d", i); break;
        }
        vga_write_at(header, 0x0E, col * MANUAL_CELL_WIDTH, row * MANUAL_CELL_HEIGHT);
    }
}

void hub_vga_update(int module_idx, int line, const char* str) {
    // Skip if module index is out of range
    if (module_idx >= g_module_count) return;

    int col = module_idx % g_cols;
    int row = module_idx / g_cols;

    // Ensure line is within cell bounds
    if (line >= MANUAL_CELL_HEIGHT - 1) return;

    // Format the string to fit cell width
    char buf[MANUAL_CELL_WIDTH + 1];
    int i = 0;
    for (; str[i] && i < MANUAL_CELL_WIDTH - 1; ++i) buf[i] = str[i];
    for (; i < MANUAL_CELL_WIDTH - 1; ++i) buf[i] = ' ';
    buf[MANUAL_CELL_WIDTH - 1] = 0;

    // Write at calculated position
    vga_write_at(buf, 0x0F, col * MANUAL_CELL_WIDTH, row * MANUAL_CELL_HEIGHT + 1 + line);
}
