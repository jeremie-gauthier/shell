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

static bool take_until_closing_brace(char c)
{
	return c != CLOSING_BRACE;
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
	if (has_opening_brace)
	{
		take_until_predicate = take_until_closing_brace;
		advance_lexer(lexer);
	}

	while (lexer->current_char && take_until_predicate(lexer->current_char))
		advance_lexer(lexer);

	if (has_opening_brace)
		advance_lexer(lexer);

	param_expansion->loc.end = lexer->pos - 1;
	const size_t parameter_loc_start = param_expansion->loc.start + (has_opening_brace ? 2 : 1);
	const size_t parameter_loc_end = param_expansion->loc.end - (has_opening_brace ? 1 : 0);
	// add 1 to loc_end to have the last char included in parameter string
	const size_t param_length = (parameter_loc_end + 1) - parameter_loc_start;

	param_expansion->parameter = ft_strndup(&lexer->input[parameter_loc_start], param_length);
	if (!param_expansion->parameter)
		ft_memdel((void **)&param_expansion);

	return param_expansion;
}

#ifdef DEBUG
void print_param_exps_vec(void **item)
{
	t_expansion_token *token = *item;

	printf("-> parameter \"%s\" at (%zu;%zu)\n", token->parameter, token->loc.start, token->loc.end);
}
#endif
