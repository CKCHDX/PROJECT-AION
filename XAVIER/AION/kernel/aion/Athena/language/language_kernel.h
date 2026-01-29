#ifndef ATHENA_LANGUAGE_KERNEL_H
#define ATHENA_LANGUAGE_KERNEL_H

#include <stddef.h>
#include <stdint.h>

// Initialize the language system
void language_initialize(void);

// Process input text/symbols
void language_process_input(const char *input, size_t len);

// Generate output based on internal state
const char* language_generate_output(void);

// Print status to VGA or log
void language_status(void);

// Update language module (called from hub)
void language_update(void);

#endif // ATHENA_LANGUAGE_KERNEL_H
