#include "token.h"
#include <stddef.h>
#include <stdio.h>

static const char *get_token_value(const t_token token)
{
	return token.value;
}

static const char *TOKEN_TYPE_STR[NB_DISTINCT_TOKENS] = {
	[Word] = "Word",
	[Unknown] = "Unknown",
	[End] = "End",
};

const char *token_type_to_str(const enum e_token_type type)
{
	return TOKEN_TYPE_STR[type];
}

void print_token(const t_token token)
{
	printf(
		"Token { [%s] (%s) }\n",
		get_token_value(token), token_type_to_str(token.type));
}
