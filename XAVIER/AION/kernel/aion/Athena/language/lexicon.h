#ifndef ATHENA_LEXICON_H
#define ATHENA_LEXICON_H

#include <stddef.h>
#include <stdint.h>

#define MAX_LEXICON_ENTRIES 64
#define MAX_WORD_LENGTH 16

typedef struct {
    char word[MAX_WORD_LENGTH];
    uint8_t frequency;
    uint8_t category;  // 0=unknown, 1=command, 2=object, 3=action, etc.
} LexiconEntry;

// Initialize lexicon with basic vocabulary
void lexicon_initialize(void);

// Add or update a word in the lexicon
int lexicon_add_word(const char *word, uint8_t category);

// Lookup a word in the lexicon
const LexiconEntry* lexicon_lookup(const char *word);

// Get lexicon statistics
size_t lexicon_get_size(void);

#endif // ATHENA_LEXICON_H
