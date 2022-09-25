#include "lexer.h"
#include "lib_char.h"
#include "lib_str.h"
#include "shell.h"
#include "token.h"

#include <stdio.h>

const char *word(const t_shell *const shell, t_lexer *const restrict lexer)
{
	const size_t start_idx = lexer->pos;

	while (lexer->current_char && ft_isgraph(lexer->current_char))
	{
		if (lexer->current_char == EXP_PARAM_CHAR)
		{
			const char *expansion = expansion_param(shell, lexer);
			// if here, concat expansion with word
			// do a loop, bc "ok$PATH$PATH" is a valid Word that must be subst'd twice
			fprintf(stderr, "subst = %s\n", expansion);
		}
		else
			advance_lexer(lexer);
	}

	return ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
}
