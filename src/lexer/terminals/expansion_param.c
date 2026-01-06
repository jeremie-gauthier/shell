#include "env.h"
#include "lexer.h"
#include "lib_arr.h"
#include "lib_char.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "shell.h"
#include "token.h"
#include <stdlib.h>

#include <stdio.h>

/*
 ** PARSING ONLY
 */

static bool take_until_closing_brace_or_subst(char c)
{
	return c != CLOSING_BRACE && c != EXP_PARAM_SEPARATOR;
}

static bool take_until_forbidden_char(char c)
{
	return ft_isalnum(c) || c == '_';
}

static t_expansion_token *create_param_expansion_token(const t_lexer *const lexer)
{
	t_expansion_token *param_expansion = malloc(sizeof(*param_expansion));
	if (!param_expansion)
		return NULL;

	param_expansion->type = Parameter;
	param_expansion->loc.start = lexer->pos;
	// default to a SimpleSubstitution type
	param_expansion->param_exp_type = SimpleSubstitution;

	param_expansion->parameter = NULL;
	param_expansion->substitution = NULL;

	return param_expansion;
}

// ! Only SimpleSubstitution is supported yet
t_expansion_token *parse_param_expansion(t_lexer *const lexer)
{
	t_expansion_token *param_expansion = create_param_expansion_token(lexer);
	if (!param_expansion)
		return NULL;

	advance_lexer(lexer);

	bool (*take_until_predicate)(char) = take_until_forbidden_char;
	const bool has_opening_brace = lexer->current_char == OPENING_BRACE;
	const size_t parameter_loc_start = param_expansion->loc.start + (has_opening_brace ? 2 : 1);
	if (has_opening_brace)
	{
		take_until_predicate = take_until_closing_brace_or_subst;
		advance_lexer(lexer);
	}

	while (lexer->current_char && take_until_predicate(lexer->current_char))
		advance_lexer(lexer);

	const size_t parameter_length = lexer->pos - parameter_loc_start;
	param_expansion->parameter = ft_strndup(&lexer->input[parameter_loc_start], parameter_length);

	if (lexer->current_char == EXP_PARAM_SEPARATOR)
	{
		advance_lexer(lexer);
		if (lexer->current_char == '-')
			param_expansion->param_exp_type = UseAlternativeValueIfNone;
		else if (lexer->current_char == '+')
			param_expansion->param_exp_type = UseAlternativeValueIfExists;
		else if (lexer->current_char == '=')
			param_expansion->param_exp_type = SetAlternativeValueIfNone;
		else if (lexer->current_char == '?')
			param_expansion->param_exp_type = ThrowErrorIfNone;

		advance_lexer(lexer);

		const size_t substitution_loc_start = lexer->pos;
		while (lexer->current_char && lexer->current_char != CLOSING_BRACE)
			advance_lexer(lexer);
		const size_t substitution_loc_end = lexer->pos;
		const size_t substitution_length = substitution_loc_end - substitution_loc_start;
		param_expansion->substitution = ft_strndup(&lexer->input[substitution_loc_start], substitution_length);
	}

	if (has_opening_brace)
		advance_lexer(lexer);

	param_expansion->loc.end = lexer->pos - 1;

	if (!param_expansion->parameter)
		ft_memdel((void **)&param_expansion);

	return param_expansion;
}
