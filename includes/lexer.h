#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stdbool.h>
#include <stddef.h>

#define WHITESPACES " \t\n\r\v\f"
#define OPERATORS "<>&|;"

typedef struct s_lexer
{
	const char *input;
	size_t pos;
	char current_char;
} t_lexer;

t_lexer lexer_create(const char *const restrict str);
t_token get_next_token(t_lexer *const restrict lexer);
void advance_lexer(t_lexer *const restrict lexer);

enum e_token_type get_token_type(char c);

/*
 ** TERMINALS
 */

void skip_whitespace(t_lexer *const restrict lexer);
const char *word(t_lexer *const restrict lexer);
t_token unknown(t_lexer *const restrict lexer);

#endif
