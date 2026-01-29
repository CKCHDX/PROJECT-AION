#include "language_kernel.h"
#include "parser.h"
#include "lexicon.h"
#include "lang_learn.h"
#include "lang_chat.h"
#include "../hub_vga.h"
#include "../utils.h"

static ParsedInput current_parsed;
static char output_buffer[64];
static uint8_t module_initialized = 0;

void language_initialize(void) {
    lexicon_initialize();
    lang_chat_initialize();
    athena_memset(&current_parsed, 0, sizeof(current_parsed));
    output_buffer[0] = '\0';
    
    // Calculate initial learning progress based on initialized vocabulary
    lang_learn_update_stats();
    
    module_initialized = 1;
    hub_vga_update(8, 0, "[LANGUAGE] Initialized");
}

void language_process_input(const char *input, size_t len) {
    if (!module_initialized || !input || len == 0) {
        return;
    }

    // Parse the input
    int result = parser_tokenize(input, len, &current_parsed);
    
    if (result > 0) {
        // Learn from the tokens
        lang_learn_from_tokens(&current_parsed);
        
        // Update learning statistics
        lang_learn_update_stats();
        
        // Generate response
        const char *response = lang_chat_respond(&current_parsed);
        
        // Copy response to output buffer
        size_t i = 0;
        while (i < 63 && response[i] != '\0') {
            output_buffer[i] = response[i];
            i++;
        }
        output_buffer[i] = '\0';
    }
}

const char* language_generate_output(void) {
    return output_buffer;
}

void language_update(void) {
    if (!module_initialized) {
        return;
    }

    // Simulate receiving input from attention/perception
    // In a real system, this would come from other modules
    static uint8_t update_counter = 0;
    update_counter++;
    
    if (update_counter % 10 == 0) {
        // Process sample input periodically
        const char *sample_input = "hello system";
        language_process_input(sample_input, athena_strlen(sample_input));
    }
    
    hub_vga_update(8, 1, "[LANGUAGE] Processing");
}

void language_status(void) {
    if (!module_initialized) {
        hub_vga_update(8, 0, "[LANGUAGE] Not initialized");
        return;
    }

    char buf[48];
    
    // Display vocabulary size
    size_t vocab_size = lexicon_get_size();
    athena_snprintf(buf, sizeof(buf), "Vocab: %d words", (int)vocab_size);
    hub_vga_update(8, 2, buf);
    
    // Display learning progress
    uint8_t progress = lang_learn_get_progress();
    athena_snprintf(buf, sizeof(buf), "Learn: %d%%", progress);
    hub_vga_update(8, 3, buf);
    
    // Display token count if available
    if (current_parsed.token_count > 0) {
        athena_snprintf(buf, sizeof(buf), "Tokens: %d", current_parsed.token_count);
        hub_vga_update(8, 4, buf);
    }
}
