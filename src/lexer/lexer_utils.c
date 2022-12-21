#include "lexer.h"
#include "lib_char.h"
#include "shell.h"
#include "token.h"
#include <stdio.h>

/// @brief This function is responsible for breaking a sentence
/// apart into tokens. One token at a time.
/// @return A generic lexer token
t_token get_next_token(const t_shell *const shell, t_lexer *const lexer)
{
	while (lexer->current_char)
	{
		if (ft_isspace(lexer->current_char))
		{
			skip_whitespace(lexer);
			continue;
		}

		if (lexer->current_char == COMMAND_SEPARATOR)
			return (t_token){.type = CommandSeparator};

		// if (lexer->current_char == '~')
		// 	return (t_token){.type = Word, .data = expansion_tilde(shell, lexer)};

		// if (lexer->current_char == '$')
		// 	return (t_token){.type = Word, .word = expansion_param(shell, lexer)};

		if (ft_isgraph(lexer->current_char))
			return (t_token){.type = Word, .word = word(lexer)};

		fprintf(stderr, "Lexer error, token not recognized\n");
		return (t_token){.type = Unknown};
	}

	return (t_token){.type = End};
}

/*
 * Advance the pos pointer and set the current_char variable.
 */
void advance_lexer(t_lexer *const lexer)
{
	lexer->pos += 1;
	lexer->current_char = lexer->input[lexer->pos];
}
