#include "perception.h"
#include "../utils.h"

// Simulated input data (could be replaced with real sensor/file input)
static const char *simulated_input = "Hello, Athena! This is a perception test.";
static size_t input_offset = 0;

void perception_initialize(void) {
    input_offset = 0;
    athena_print("[ATHENA][PERCEPTION] Perception initialized\n");
}

size_t perception_read(uint8_t *buffer, size_t max_size) {
    size_t input_len = athena_strlen(simulated_input);
    size_t remaining = (input_len > input_offset) ? (input_len - input_offset) : 0;
    size_t to_read = (remaining < max_size) ? remaining : max_size;
    if (to_read > 0) {
        athena_memcpy(buffer, simulated_input + input_offset, to_read);
        input_offset += to_read;
        athena_print("[ATHENA][PERCEPTION] Read bytes\n");
        return to_read;
    }
    return 0;
}

void perception_status(void) {
    size_t input_len = athena_strlen(simulated_input);
    // For demonstration, just print offset (expand as needed)
    vga_printf("[ATHENA][PERCEPTION] Offset: %d/%d\n", (int)input_offset, (int)input_len);
}
