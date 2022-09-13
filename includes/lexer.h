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
	t_token *tokens;
	size_t tokens_len;
	size_t tokens_cap;
	size_t input_idx;
	bool has_error;
} t_lexer;

t_lexer lexer(const char *str);
void free_lexer(t_lexer *lexer);

enum e_token_type get_token_type(char c);

/*
 ** RULES
 */
t_token whitespace(t_lexer *const restrict lexer);
t_token word(t_lexer *const restrict lexer);
t_token unknown(t_lexer *const restrict lexer);
t_token operator(t_lexer *const restrict lexer);

static t_token (*RULES[NB_DISTINCT_TOKENS])(t_lexer *const lexer) = {
	[Whitespace] = whitespace,
	[Word] = word,
	[Operator] = operator,
	[Unknown] = unknown,
};

/*
 ** DEBUG
 */
void print_tokens(const t_token *tokens);
void print_token(const t_token token);
const char *token_type_to_str(const enum e_token_type type);

#endif
