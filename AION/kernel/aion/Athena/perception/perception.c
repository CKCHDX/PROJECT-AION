#include "perception.h"
#include "../utils.h"
#include "../hub_vga.h"

static const char *simulated_input = "Hello, Athena! This is a perception test.";
static size_t input_offset = 0;

void perception_initialize(void) {
    input_offset = 0;
    hub_vga_update(HUB_VGA_MODULE_PERCEPTION, 0, "[PERCEPTION] Initialized");
}

size_t perception_read(uint8_t *buffer, size_t max_size) {
    size_t input_len = athena_strlen(simulated_input);
    size_t remaining = (input_len > input_offset) ? (input_len - input_offset) : 0;
    size_t to_read = (remaining < max_size) ? remaining : max_size;
    if (to_read > 0) {
        athena_memcpy(buffer, simulated_input + input_offset, to_read);
        input_offset += to_read;
        char buf[48];
        athena_snprintf(buf, sizeof(buf), "[PERCEPTION] Read %d bytes", (int)to_read);
        hub_vga_update(HUB_VGA_MODULE_PERCEPTION, 1, buf);
        return to_read;
    }
    return 0;
}

void perception_status(void) {
    size_t input_len = athena_strlen(simulated_input);
    char buf[48];
    athena_snprintf(buf, sizeof(buf), "[PERCEPTION] Offset: %d/%d", (int)input_offset, (int)input_len);
    hub_vga_update(HUB_VGA_MODULE_PERCEPTION, 2, buf);
}
