#ifndef ATHENA_LANG_LEARN_H
#define ATHENA_LANG_LEARN_H

#include <stddef.h>
#include <stdint.h>
#include "parser.h"

// Learn from parsed input tokens
void lang_learn_from_tokens(const ParsedInput *parsed);

// Update language learning statistics
void lang_learn_update_stats(void);

// Get learning progress
uint8_t lang_learn_get_progress(void);

#endif // ATHENA_LANG_LEARN_H
