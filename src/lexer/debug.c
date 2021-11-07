#include <stddef.h>
#include "token.h"
#include <stdio.h>

static const char *get_token_value(const t_token token)
{
	return token.value;
}

static const char *get_token_type(const t_token token)
{
	switch (token.type)
	{
	case Word:
		return "Word";
	case Operator:
		return "Operator";
	default:
		return "unknown";
	}
}

void print_tokens(const t_token *tokens)
{
	while (tokens->type != End)
	{
		printf(
			"Token { %s (%s) }\n",
			get_token_value(*tokens), get_token_type(*tokens));
		tokens++;
	}
}
