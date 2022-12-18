#include "env.h"
#include "lexer.h"
#include "lib_char.h"
#include "lib_str.h"
#include "shell.h"

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
