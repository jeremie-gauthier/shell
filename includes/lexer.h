#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#define WHITESPACES " \t\n\r\v\f"

const t_token *lexer(const char *str);

void print_tokens(const t_token *tokens);

#endif
