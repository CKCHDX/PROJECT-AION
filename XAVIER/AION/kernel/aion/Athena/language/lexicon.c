#include "lexicon.h"
#include "../utils.h"

static LexiconEntry lexicon[MAX_LEXICON_ENTRIES];
static size_t lexicon_size = 0;

// Helper function to compare strings (case-sensitive)
static int str_compare(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            return 0;
        }
        s1++;
        s2++;
    }
    return (*s1 == *s2);
}

// Helper function to copy string with size limit
static void str_copy(char *dest, const char *src, size_t max_len) {
    size_t i = 0;
    while (i < max_len - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void lexicon_initialize(void) {
    lexicon_size = 0;
    
    // Initialize with basic vocabulary
    lexicon_add_word("hello", 1);   // command
    lexicon_add_word("status", 1);  // command
    lexicon_add_word("learn", 3);   // action
    lexicon_add_word("think", 3);   // action
    lexicon_add_word("data", 2);    // object
    lexicon_add_word("system", 2);  // object
}

int lexicon_add_word(const char *word, uint8_t category) {
    if (!word || lexicon_size >= MAX_LEXICON_ENTRIES) {
        return -1;
    }

    // Check if word already exists
    for (size_t i = 0; i < lexicon_size; i++) {
        if (str_compare(lexicon[i].word, word)) {
            // Word exists, increment frequency
            if (lexicon[i].frequency < 255) {
                lexicon[i].frequency++;
            }
            // Update category if provided
            if (category != 0) {
                lexicon[i].category = category;
            }
            return i;
        }
    }

    // Add new word
    str_copy(lexicon[lexicon_size].word, word, MAX_WORD_LENGTH);
    lexicon[lexicon_size].frequency = 1;
    lexicon[lexicon_size].category = category;
    lexicon_size++;
    
    return lexicon_size - 1;
}

const LexiconEntry* lexicon_lookup(const char *word) {
    if (!word) {
        return 0;
    }

    for (size_t i = 0; i < lexicon_size; i++) {
        if (str_compare(lexicon[i].word, word)) {
            return &lexicon[i];
        }
    }
    
    return 0;  // Not found
}

size_t lexicon_get_size(void) {
    return lexicon_size;
}
