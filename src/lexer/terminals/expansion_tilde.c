#include "env.h"
#include "lexer.h"
#include "lib_char.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "shell.h"
#include "token.h"
#include <stdbool.h>
#include <stdlib.h>

static const char *concat_path(const t_shell *const shell, t_lexer *const lexer, const char *prefix)
{
	(void)shell;
	(void)lexer;
	// const char *path = word(shell, lexer);
	const char *path = ft_strdup("FIX ME, RESTORE ABOVE LINE");
	const char *word = ft_strjoin(prefix, path, "");
	ft_strdel((char **)&path);
	return word;
}

// ~ => The value of $HOME
// ~/foo => $HOME/foo
// ~+/foo => $PWD/foo
// ~-/foo => ${OLDPWD-'~-'}/foo
const char *expansion_tilde(const t_shell *const shell, t_lexer *const lexer)
{
	advance_lexer(lexer);

	char *prefix = NULL;
	if (lexer->current_char == PATH_SEPARATOR || ft_isspace(lexer->current_char) || lexer->current_char == '\0')
		prefix = env_get(shell->env, "HOME");
	else if (lexer->current_char == '+')
	{
		advance_lexer(lexer);
		prefix = env_get(shell->env, "PWD");
	}
	else if (lexer->current_char == '-')
	{
		advance_lexer(lexer);
		prefix = env_get(shell->env, "OLDPWD");
	}

	if (!prefix)
	{
		// skip next chars
		// const char *tmp = word(shell, lexer);
		// ft_strdel((char **)&tmp);
		// return NULL;
	}
	return concat_path(shell, lexer, prefix);
}

static bool is_end_of_word(const char c)
{
	return ft_isspace(c) || c == '\0';
}

t_expansion_token *parse_tilde_expansion(t_lexer *const lexer)
{
	t_expansion_token *tilde_expansion = malloc(sizeof(*tilde_expansion));
	if (!tilde_expansion)
		return NULL;

	tilde_expansion->loc.start = lexer->pos;
	advance_lexer(lexer);

	if (lexer->current_char == '+')
	{
		tilde_expansion->tilde_exp_type = Pwd;
		advance_lexer(lexer);
	}
	else if (lexer->current_char == '-')
	{
		tilde_expansion->tilde_exp_type = Oldpwd;
		advance_lexer(lexer);
	}
	else
	{
		if (lexer->current_char == PATH_SEPARATOR || is_end_of_word(lexer->current_char))
			tilde_expansion->tilde_exp_type = Home;
		else
			tilde_expansion->tilde_exp_type = Literal;

		tilde_expansion->loc.end = lexer->pos;
		const size_t param_length = (tilde_expansion->loc.end + 1) - tilde_expansion->loc.start;
		tilde_expansion->parameter = ft_strndup(&lexer->input[tilde_expansion->loc.start], param_length);
		if (!tilde_expansion->parameter)
			ft_memdel((void **)&tilde_expansion);

		return tilde_expansion;
	}

	if (!(lexer->current_char == PATH_SEPARATOR || is_end_of_word(lexer->current_char)))
		tilde_expansion->tilde_exp_type = Literal;

	tilde_expansion->loc.end = lexer->pos;
	const size_t param_length = (tilde_expansion->loc.end + 1) - tilde_expansion->loc.start;
	tilde_expansion->parameter = ft_strndup(&lexer->input[tilde_expansion->loc.start], param_length);
	if (!tilde_expansion->parameter)
		ft_memdel((void **)&tilde_expansion);

	return tilde_expansion;
}
