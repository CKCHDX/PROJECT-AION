#include "parser.h"
#include "../utils.h"

int parser_is_delimiter(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || 
            c == ',' || c == '.' || c == '!' || c == '?');
}

int parser_tokenize(const char *input, size_t len, ParsedInput *result) {
    if (!input || !result || len == 0) {
        return -1;
    }

    result->token_count = 0;
    size_t token_idx = 0;
    size_t char_idx = 0;
    int in_token = 0;

    for (size_t i = 0; i < len && result->token_count < MAX_TOKENS; i++) {
        char c = input[i];
        
        if (c == '\0') {
            break;
        }

        if (parser_is_delimiter(c)) {
            if (in_token) {
                // End current token
                result->tokens[result->token_count][char_idx] = '\0';
                result->token_count++;
                in_token = 0;
                char_idx = 0;
            }
        } else {
            if (!in_token) {
                // Start new token
                in_token = 1;
                char_idx = 0;
            }
            if (char_idx < MAX_TOKEN_LENGTH - 1) {
                result->tokens[result->token_count][char_idx++] = c;
            }
        }
    }

    // Handle last token if still in one
    if (in_token && result->token_count < MAX_TOKENS) {
        result->tokens[result->token_count][char_idx] = '\0';
        result->token_count++;
    }

    return result->token_count;
}
