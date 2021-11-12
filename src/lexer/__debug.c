#include <stddef.h>
#include "token.h"
#include <stdio.h>

static const char *get_token_value(const t_token token)
{
	return token.value;
}

static const char *TOKEN_TYPE_STR[NB_DISTINCT_TOKENS] = {
	[Whitespace] = "Whitespace",
	[Word] = "Word",
	[Operator] = "Operator",
	[Redirection] = "Redirection",
	[Pipe] = "Pipe",
	[Separator] = "Separator",
	[Logical] = "Logical",
	[Number] = "Number",
	[End] = "End",
	[Unknown] = "Unknown",
};

const char *token_type_to_str(const enum e_token_type type)
{
	return TOKEN_TYPE_STR[type];
}

void print_tokens(const t_token *tokens)
{
	while (tokens->type != End)
	{
		printf(
			"Token { [%s] (%s) }\n",
			get_token_value(*tokens), token_type_to_str(tokens->type));
		tokens++;
	}
}
