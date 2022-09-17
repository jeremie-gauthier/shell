#include "lexer.h"
#include "lib_char.h"
#include "token.h"
#include <stdio.h>

/*
 *	This function is responsible for breaking a sentence
 *	apart into tokens. One token at a time.
 */
t_token get_next_token(t_lexer *const restrict lexer)
{
	while (lexer->current_char)
	{
		if (ft_isspace(lexer->current_char))
		{
			skip_whitespace(lexer);
			continue;
		}

		if (ft_isgraph(lexer->current_char))
			return (t_token){.type = Word, .value = word(lexer)};

		printf("Lexer error, token not recognized\n");
		return (t_token){.type = Unknown, .value = NULL};
	}

	return (t_token){.type = End, .value = NULL};
}

/*
 * Advance the pos pointer and set the current_char variable.
 */
void advance_lexer(t_lexer *const restrict lexer)
{
	lexer->pos += 1;
	lexer->current_char = lexer->input[lexer->pos];
}
