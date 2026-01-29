#include "lang_learn.h"
#include "lexicon.h"
#include "../utils.h"

static uint8_t learning_progress = 0;

void lang_learn_from_tokens(const ParsedInput *parsed) {
    if (!parsed) {
        return;
    }

    for (uint8_t i = 0; i < parsed->token_count; i++) {
        const char *token = parsed->tokens[i];
        
        // Check if word exists in lexicon
        const LexiconEntry *entry = lexicon_lookup(token);
        
        if (entry) {
            // Word exists, increase frequency (handled by lexicon_add_word)
            lexicon_add_word(token, entry->category);
        } else {
            // New word, add with unknown category
            lexicon_add_word(token, 0);
        }
    }
}

void lang_learn_update_stats(void) {
    // Update learning progress based on vocabulary size
    size_t vocab_size = lexicon_get_size();
    
    if (vocab_size <= 10) {
        learning_progress = 10;
    } else if (vocab_size <= 20) {
        learning_progress = 25;
    } else if (vocab_size <= 40) {
        learning_progress = 50;
    } else if (vocab_size <= 60) {
        learning_progress = 75;
    } else {
        learning_progress = 100;
    }
}

uint8_t lang_learn_get_progress(void) {
    return learning_progress;
}
