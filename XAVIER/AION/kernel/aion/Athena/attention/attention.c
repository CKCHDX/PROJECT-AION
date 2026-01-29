#include "attention.h"
#include "../hub_vga.h"
#include "../utils.h"

static AttentionState g_attention;

void attention_initialize(void) {
    athena_memset(&g_attention, 0, sizeof(g_attention));
    hub_vga_update(4, 0, "[ATTENTION] Initialized");
}

// Simple winner-take-all: picks the top N salience candidates
void attention_update(const AttentionFocus* candidates, size_t n) {
    // Copy and sort by salience (descending)
    AttentionFocus sorted[ATTENTION_MAX_FOCI * 2];
    size_t count = n > ATTENTION_MAX_FOCI * 2 ? ATTENTION_MAX_FOCI * 2 : n;
    athena_memcpy(sorted, candidates, count * sizeof(AttentionFocus));

    // Simple bubble sort for small N
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (sorted[j].salience > sorted[i].salience) {
                AttentionFocus tmp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = tmp;
            }
        }
    }

    // Fill focus buffer with top N
    g_attention.count = count < ATTENTION_MAX_FOCI ? count : ATTENTION_MAX_FOCI;
    for (size_t i = 0; i < g_attention.count; ++i) {
        g_attention.foci[i] = sorted[i];
        g_attention.foci[i].activation = 1.0f; // All get full attention for now
    }

    hub_vga_update(4, 1, "[ATTENTION] Updated");
}

const AttentionState* attention_get_state(void) {
    return &g_attention;
}

void attention_status(void) {
    char line[40];
    athena_snprintf(line, sizeof(line), "[ATTN] Foci: %d", (int)g_attention.count);
    hub_vga_update(4, 2, line);

    // Print each focus, salience as integer percentage (e.g., 0.82 -> 82%)
    for (size_t i = 0; i < g_attention.count && i < 4; ++i) {
        char buf[40];
        int sal = (int)(g_attention.foci[i].salience * 100); // Convert to percent
        athena_snprintf(buf, sizeof(buf), "ID:%d S:%d%%",
                        (int)g_attention.foci[i].id,
                        sal
        );
        hub_vga_update(4, 3 + i, buf);
    }
}
