#include "lexer.h"
#include "lib_arr.h"
#include "lib_char.h"
#include "lib_ht.h"
#include "lib_str.h"
#include "shell.h"

#include <stdio.h>

static const char *param_subst(const t_shell *const shell, const char *const param, const char *const word)
{
	const char *value = ht_get(shell->cache.global, param);
	const char test_operator = word[0];

	if (test_operator == '-')
		return value ? ft_strdup(value) : ft_strdup(&word[1]);
	if (test_operator == '=')
	{
		if (value)
			return ft_strdup(value);
		ht_set(shell->cache.global, param, &word[1]);
		return ft_strdup(&word[1]);
	}
	if (test_operator == '+')
		return value ? ft_strdup(&word[1]) : NULL;
	return NULL;
}

// ! Negative offset are not handled
static const char *param_substring_subst(const char *const param, const int start, const int len)
{
	if (!param || len <= 0 || start < 0)
		return NULL;
	return ft_strndup(&param[start], len);
}

// complex subst = ${PATH:...}
static const char *complex_subst(const t_shell *const shell, t_lexer *const restrict lexer)
{
	advance_lexer(lexer);

	size_t start_idx = lexer->pos;
	while (lexer->current_char && lexer->current_char != CLOSING_BRACE)
		advance_lexer(lexer);

	const char *const expansion = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
	const char *const *const expansion_vector = ft_strsplit(expansion, ':');
	ft_strdel((char **)&expansion);
	const size_t expansion_counter = ft_arr_len(expansion_vector);

	const char *param = ht_get(shell->cache.global, expansion_vector[0]);
	char *subst = NULL;
	if (expansion_counter == 1 && param)
		subst = ft_strdup(param);
	else if (expansion_counter == 2)
	{
		if (ft_strisnum(expansion_vector[1]))
		{
			const int start = ft_atoi(expansion_vector[1]);
			if (param)
				subst = ft_strdup(&param[start]);
		}
		else
			subst = (char *)param_subst(shell, expansion_vector[0], expansion_vector[1]);
	}
	else if (expansion_counter == 3)
	{
		const int start = ft_atoi(expansion_vector[1]);
		const int len = ft_atoi(expansion_vector[2]);
		subst = (char *)param_substring_subst(param, start, len);
	}
	ft_arr_free((char **)expansion_vector, expansion_counter);
	advance_lexer(lexer);

	return subst;
}

// simple subst = $PATH
static const char *simple_subst(const t_shell *const shell, t_lexer *const restrict lexer)
{
	const size_t start_idx = lexer->pos;

	while (lexer->current_char && (ft_isalnum(lexer->current_char) || lexer->current_char == '_'))
		advance_lexer(lexer);

	const char *const param = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
	const char *subst = ht_get(shell->cache.global, param);
	ft_strdel((char **)&param);

	if (subst)
		return ft_strdup(subst);
	return NULL;
}

const char *expansion_param(const t_shell *const shell, t_lexer *const restrict lexer)
{
	advance_lexer(lexer);
	if (lexer->current_char == OPENING_BRACE)
		return complex_subst(shell, lexer);

	if (ft_isalpha(lexer->current_char) || lexer->current_char == '_')
		return simple_subst(shell, lexer);

	return ft_strdup("$");
}
