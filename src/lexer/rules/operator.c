#include "lexer.h"
#include "lib_str.h"
#include "token.h"

static enum e_token_type get_operator_type(const char c);
static t_token (*RULES_OPERATOR[NB_DISTINCT_TOKENS])(t_lexer *const lexer);

t_token operator(t_lexer *const restrict lexer)
{
	const enum e_token_type token_type = get_operator_type(lexer->input[lexer->input_idx]);
	t_token token = RULES_OPERATOR[token_type](lexer);
	return token;
}

static enum e_token_type get_operator_type(const char c)
{
	if (c == '<' || c == '>')
		return Redirection;
	if (c == ';')
		return Separator;

	// char '|' is ambiguous as it can lead to a pipe or a logical or
	if (c == '&')
		return Logical;
	return Unknown;
}

static t_token redirection(t_lexer *const lexer)
{
	t_token token = {.type = Redirection, .value = NULL};
	const char cur_char = lexer->input[lexer->input_idx];
	const char next_char = lexer->input[lexer->input_idx + 1];

	if (ft_strchr("<>&", next_char))
	{
		// <> and >< are not valid redirection, treat it as 2 separate tokens
		if ((cur_char == '<' && next_char != '>') || (cur_char == '>' && next_char != '<'))
		{
			token.value = ft_strndup(&lexer->input[lexer->input_idx], 2);
			lexer->input_idx += 2;
			return token;
		}
	}
	token.value = ft_strndup(&lexer->input[lexer->input_idx], 1);
	lexer->input_idx++;
	return token;
}

static t_token ambiguous_operator(t_lexer *const lexer)
{
	const char next_char = lexer->input[lexer->input_idx + 1];

	if (next_char == '|')
	{
		t_token token = {
			.type = Logical,
			.value = ft_strndup(&lexer->input[lexer->input_idx], 2)};
		lexer->input_idx += 2;
		return token;
	}

	t_token token = {
		.type = Pipe,
		.value = ft_strndup(&lexer->input[lexer->input_idx], 1)};
	lexer->input_idx++;
	return token;
}

static t_token separator(t_lexer *const lexer)
{
	t_token token = {
		.type = Separator,
		.value = ft_strndup(&lexer->input[lexer->input_idx], 1)};
	lexer->input_idx++;
	return token;
}

static t_token logical(t_lexer *const lexer)
{
	const char next_char = lexer->input[lexer->input_idx + 1];

	if (next_char != '&')
		return (t_token){.type = Unknown, .value = NULL};

	t_token token = {
		.type = Logical,
		.value = ft_strndup(&lexer->input[lexer->input_idx], 2)};
	lexer->input_idx += 2;
	return token;
}

static t_token (*RULES_OPERATOR[NB_DISTINCT_TOKENS])(t_lexer *const lexer) = {
	[Redirection] = redirection,
	[Separator] = separator,
	[Logical] = logical,
	[Unknown] = ambiguous_operator};
