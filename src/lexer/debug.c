#include <stddef.h>
#include "token.h"
#include <stdio.h>

static const char *get_token_value(const t_token token)
{
	return token.value;
}

const char *token_type_to_str(const enum e_token_type type)
{
	switch (type)
	{
		case Whitespace:
			return "Whitespace";
		case Word:
			return "Word";
		case Operator:
			return "Operator";
		case Number:
			return "Number";
		case End:
			return "End";
		default:
			return "Unknown";
	}
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
