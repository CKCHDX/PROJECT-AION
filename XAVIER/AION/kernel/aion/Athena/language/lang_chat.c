#include "lang_chat.h"
#include "lexicon.h"
#include "../utils.h"

#define MAX_RESPONSE_LENGTH 64

static char last_response[MAX_RESPONSE_LENGTH];

void lang_chat_initialize(void) {
    last_response[0] = '\0';
}

const char* lang_chat_respond(const ParsedInput *parsed) {
    if (!parsed || parsed->token_count == 0) {
        athena_snprintf(last_response, MAX_RESPONSE_LENGTH, "No input");
        return last_response;
    }

    // Simple response logic based on first token
    const char *first_token = parsed->tokens[0];
    const LexiconEntry *entry = lexicon_lookup(first_token);

    if (entry) {
        // Known word
        switch (entry->category) {
            case 1: // command
                athena_snprintf(last_response, MAX_RESPONSE_LENGTH, 
                    "Command: %s", first_token);
                break;
            case 2: // object
                athena_snprintf(last_response, MAX_RESPONSE_LENGTH, 
                    "Object: %s", first_token);
                break;
            case 3: // action
                athena_snprintf(last_response, MAX_RESPONSE_LENGTH, 
                    "Action: %s", first_token);
                break;
            default:
                athena_snprintf(last_response, MAX_RESPONSE_LENGTH, 
                    "Known: %s", first_token);
                break;
        }
    } else {
        // Unknown word
        athena_snprintf(last_response, MAX_RESPONSE_LENGTH, 
            "Unknown: %s", first_token);
    }

    return last_response;
}

const char* lang_chat_get_last_response(void) {
    return last_response;
}
