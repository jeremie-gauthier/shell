#include "lexer.h"
#include "lib_char.h"
#include "lib_ht.h"
#include "lib_str.h"
#include "shell.h"

#include <stdio.h>

// complex subst = ${PATH:...}
static const char *complex_subst(const t_shell *const shell, t_lexer *const restrict lexer)
{
	(void)shell;
	advance_lexer(lexer);
	return NULL;
}

// simple subst = $PATH
static const char *simple_subst(const t_shell *const shell, t_lexer *const restrict lexer)
{
	const size_t start_idx = lexer->pos;

	advance_lexer(lexer);
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
