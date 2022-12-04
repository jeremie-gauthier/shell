#include "env.h"
#include "lexer.h"
#include "lib_arr.h"
#include "lib_char.h"
#include "lib_str.h"
#include "shell.h"

#include <stdio.h>

static char *word_expansion(const t_shell *const shell, const char *const param, const char *const word)
{
	const char *value = env_get(shell->env, param);
	const char test_operator = word[0];

	if (test_operator == '-')
		return value ? ft_strdup(value) : ft_strdup(&word[1]);
	if (test_operator == '=')
	{
		if (value)
			return ft_strdup(value);
		return ft_strdup(&word[1]);
	}
	if (test_operator == '+')
		return value ? ft_strdup(&word[1]) : NULL;
	return NULL;
}

// ! Negative offset are not handled
static char *substring_expansion(const t_shell *const shell, const char *const param, const char *const start_str, const char *len_str)
{
	const char *subst = env_get(shell->env, param);
	if (!subst)
		return NULL;

	const size_t start = (size_t)ft_atoi(start_str);
	const size_t len = len_str ? (size_t)ft_atoi(len_str) : ft_strlen(subst);

	if (!subst || len <= 0 || start < 0)
		return NULL;
	return ft_strndup(&subst[start], len);
}

static char *param_subst(const t_shell *const shell, const char *const param)
{
	const char *subst = env_get(shell->env, param);
	if (subst)
		return ft_strdup(subst);
	return NULL;
}

// complex subst = ${PATH:...}
static const char *complex_subst(const t_shell *const shell, t_lexer *const lexer)
{
	advance_lexer(lexer);

	size_t start_idx = lexer->pos;
	while (lexer->current_char && lexer->current_char != CLOSING_BRACE)
		advance_lexer(lexer);

	const char *const exp = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
	const char *const *const expv = ft_strsplit(exp, ':');
	ft_strdel((char **)&exp);
	const size_t expc = ft_arr_len(expv);

	char *subst = NULL;
	if (expc == 1)
		subst = param_subst(shell, PARAM(expv));
	else if (expc == 2)
	{
		if (ft_strisnum(expv[1]))
			subst = substring_expansion(shell, PARAM(expv), START(expv), LEN(expv));
		else
			subst = word_expansion(shell, PARAM(expv), WORD(expv));
	}
	else if (expc == 3)
		subst = substring_expansion(shell, PARAM(expv), START(expv), LEN(expv));

	ft_arr_free((char **)expv, expc);
	advance_lexer(lexer);

	return subst;
}

// simple subst = $PATH
static const char *simple_subst(const t_shell *const shell, t_lexer *const lexer)
{
	const size_t start_idx = lexer->pos;

	while (lexer->current_char && (ft_isalnum(lexer->current_char) || lexer->current_char == '_'))
		advance_lexer(lexer);

	const char *const param = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
	const char *subst = param_subst(shell, param);
	ft_strdel((char **)&param);

	return subst;
}

const char *expansion_param(const t_shell *const shell, t_lexer *const lexer)
{
	advance_lexer(lexer);
	if (lexer->current_char == OPENING_BRACE)
		return complex_subst(shell, lexer);

	if (ft_isalpha(lexer->current_char) || lexer->current_char == '_')
		return simple_subst(shell, lexer);

	return ft_strdup("$");
}

/*
 ** PARSING ONLY
 */

// t_expansion_token parse_expansion_param(const t_shell *const shell, t_lexer *const lexer)
// {
// 	advance_lexer(lexer);
// 	if (lexer->current_char == OPENING_BRACE)
// 		return complex_subst(shell, lexer);

// 	if (ft_isalpha(lexer->current_char) || lexer->current_char == '_')
// 		return simple_subst(shell, lexer);

// 	return ft_strdup("$");
// }
