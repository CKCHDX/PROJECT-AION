#ifndef ATHENA_LANG_CHAT_H
#define ATHENA_LANG_CHAT_H

#include <stddef.h>
#include <stdint.h>
#include "parser.h"

// Initialize chat interface
void lang_chat_initialize(void);

// Process chat input and generate response
const char* lang_chat_respond(const ParsedInput *parsed);

// Get last response
const char* lang_chat_get_last_response(void);

#endif // ATHENA_LANG_CHAT_H
