#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"

static bool insert_token(t_lexer *lexer, t_token new_token);
static t_lexer empty_lexer(void);

t_lexer lexer(const char *str)
{
	t_lexer lexer = {
		.input = str,
		.input_idx = 0,
		.tokens = malloc(sizeof(t_token) * DEFAULT_TOKEN_LIST_CAPACITY),
		.tokens_len = 0,
		.tokens_cap = DEFAULT_TOKEN_LIST_CAPACITY,
	};

	if (lexer.tokens == NULL)
		return empty_lexer();

	while (lexer.input[lexer.input_idx])
	{
		t_token new_token;
		const enum e_token_type token_type = get_token_type(lexer.input[lexer.input_idx]);

		switch (token_type)
		{
			case Whitespace:
				parse_whitespace(&lexer);
				continue;
			case Word:
				new_token = parse_word(&lexer);
				break;
			case Number:
				new_token = parse_number(&lexer);
				break;
			default:
				lexer.input_idx++;
				continue;
		}

		if (new_token.value && !insert_token(&lexer, new_token))
		{
			free_lexer(&lexer);
			return empty_lexer();
		}
	}

	t_token eof_token = {
		.type = End,
		.value = NULL,
	};

	if (!insert_token(&lexer, eof_token))
	{
		free_lexer(&lexer);
		return empty_lexer();
	}

	return lexer;
}


void free_lexer(t_lexer *lexer)
{
	while (lexer->tokens_len--)
		free((void *)lexer->tokens[lexer->tokens_len].value);
	free((void *)lexer->tokens);
	lexer->tokens_cap = 0;
	lexer->input_idx = 0;
}

static bool insert_token(t_lexer *lexer, t_token new_token)
{
	if (lexer->tokens_len == lexer->tokens_cap)
	{
		lexer->tokens_cap *= 2;
		lexer->tokens = (t_token *)realloc(lexer->tokens,
			sizeof(t_token) * lexer->tokens_cap);
		if (lexer->tokens == NULL)
			return false;
	}
	lexer->tokens[lexer->tokens_len++] = new_token;
	return true;
}

static t_lexer empty_lexer(void)
{
	t_lexer lexer = {
		.input = NULL,
		.input_idx = 0,
		.tokens = NULL,
		.tokens_len = 0,
		.tokens_cap = 0,
	};
	return lexer;
}
