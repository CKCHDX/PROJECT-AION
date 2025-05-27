#include "learning.h"
#include "../memory/memory.h"
#include "../utils.h"
#include "../hub_vga.h"

typedef struct {
    uint8_t center;
    uint16_t count;
} Cluster;

static Cluster clusters[MAX_CLUSTERS];
static uint8_t num_clusters = 0;

static void cluster_data(const uint8_t *data, size_t size) {
    num_clusters = 0;
    for (size_t i = 0; i < size; ++i) {
        uint8_t val = data[i];
        int found = 0;
        for (uint8_t c = 0; c < num_clusters; ++c) {
            if (clusters[c].center == val) {
                clusters[c].count++;
                found = 1;
                break;
            }
        }
        if (!found && num_clusters < MAX_CLUSTERS) {
            clusters[num_clusters].center = val;
            clusters[num_clusters].count = 1;
            num_clusters++;
        }
    }
}

void learning_initialize(void) {
    for (int i = 0; i < MAX_CLUSTERS; ++i) {
        clusters[i].center = 0;
        clusters[i].count = 0;
    }
    num_clusters = 0;
    hub_vga_update(HUB_VGA_MODULE_LEARNING, 0, "[LEARNING] Initialized");
}

void learning_process(void) {
    size_t data_size;
    const uint8_t *data = memory_retrieve(&data_size);
    if (data && data_size > 0) {
        cluster_data(data, data_size);
        hub_vga_update(HUB_VGA_MODULE_LEARNING, 1, "[LEARNING] Processed memory");
    }
}

void learning_status(void) {
    char buf[48];
    athena_snprintf(buf, sizeof(buf), "[LEARNING] Clusters: %d", num_clusters);
    hub_vga_update(HUB_VGA_MODULE_LEARNING, 2, buf);
    if (num_clusters > 0) {
        athena_snprintf(buf, sizeof(buf), "C0: 0x%02x n=%d", clusters[0].center, clusters[0].count);
        hub_vga_update(HUB_VGA_MODULE_LEARNING, 3, buf);
    }
}
