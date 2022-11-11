#ifndef LEXER_H
#define LEXER_H

#include "shell.h"
#include "token.h"
#include <stdbool.h>
#include <stddef.h>

#define WHITESPACES " \t\n\r\v\f"
#define OPERATORS "<>&|;"
#define EXP_PARAM_CHAR '$'
#define OPENING_BRACE '{'
#define CLOSING_BRACE '}'
#define EXP_PARAM_SEPARATOR ':'

#define PARAM(expv) (expv[0])
#define WORD(expv) (expv[1])
#define START(expv) (expv[1])
#define LEN(expv) (expv[2])

typedef struct s_lexer
{
	const char *input;
	size_t pos;
	char current_char;
} t_lexer;

t_lexer lexer_create(const char *const restrict str);
t_token get_next_token(const t_shell *const shell, t_lexer *const restrict lexer);
void advance_lexer(t_lexer *const restrict lexer);

enum e_token_type get_token_type(char c);

/*
 ** TERMINALS
 */

void skip_whitespace(t_lexer *const restrict lexer);
const char *word(const t_shell *const shell, t_lexer *const restrict lexer);
t_token unknown(t_lexer *const restrict lexer);
const char *expansion_param(const t_shell *const shell, t_lexer *const restrict lexer);
const char *expansion_tilde(const t_shell *const shell, t_lexer *const restrict lexer);

#endif
