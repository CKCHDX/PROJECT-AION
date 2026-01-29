#ifndef ATHENA_PARSER_H
#define ATHENA_PARSER_H

#include <stddef.h>
#include <stdint.h>

#define MAX_TOKENS 8
#define MAX_TOKEN_LENGTH 16

typedef struct {
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    uint8_t token_count;
} ParsedInput;

// Parse input text into tokens
int parser_tokenize(const char *input, size_t len, ParsedInput *result);

// Check if a character is a delimiter
int parser_is_delimiter(char c);

#endif // ATHENA_PARSER_H
