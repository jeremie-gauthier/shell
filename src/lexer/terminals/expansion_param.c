#include "lexer.h"
#include "lib_char.h"
#include "lib_ht.h"
#include "lib_str.h"
#include "shell.h"

#include <stdio.h>

// complex subst = ${PATH:...}
static const char *complex_subst(const t_shell *const shell, t_lexer *const restrict lexer)
{
	advance_lexer(lexer);

	size_t start_idx = lexer->pos;
	while (lexer->current_char && lexer->current_char != CLOSING_BRACE && lexer->current_char != EXP_PARAM_SEPARATOR)
		advance_lexer(lexer);

	const char *const param = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
	const char *subst = ht_get(shell->cache.global, param);

	if (lexer->current_char == EXP_PARAM_SEPARATOR)
	{
		advance_lexer(lexer);

		const char test_operator = lexer->current_char;
		advance_lexer(lexer);

		start_idx = lexer->pos;
		while (lexer->current_char && lexer->current_char != CLOSING_BRACE)
			advance_lexer(lexer);
		const char *const word = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);

		if (subst)
		{
			if (test_operator == '+')
			{
				advance_lexer(lexer);
				ft_strdel((char **)&param);
				return word;
			}
		}
		else
		{
			if (test_operator == '-')
			{
				advance_lexer(lexer);
				ft_strdel((char **)&param);
				return word;
			}
			if (test_operator == '=')
			{
				advance_lexer(lexer);
				ht_set(shell->cache.global, param, word);
				ft_strdel((char **)&param);
				return word;
			}
		}
	}

	ft_strdel((char **)&param);
	advance_lexer(lexer);

	if (subst)
		return ft_strdup(subst);
	return NULL;
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
