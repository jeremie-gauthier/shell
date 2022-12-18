#include "lexer.h"
#include "lib_char.h"
#include "lib_str.h"
#include "shell.h"
#include "token.h"

#include <stdio.h>

t_word_token word(const t_shell *const shell, t_lexer *const lexer)
{
	size_t start_idx = lexer->pos;
	char *word = NULL;

	while (lexer->current_char && ft_isgraph(lexer->current_char) && lexer->current_char != COMMAND_SEPARATOR)
	{
		// if (lexer->current_char == EXP_PARAM_CHAR)
		// {
		// 	// if there are a Word before the expansion char
		// 	if (start_idx != lexer->pos)
		// 		word = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);

		// 	const char *const expansion = expansion_param(shell, lexer);
		// 	if (!expansion)
		// 		continue;

		// 	// concat expansion with word
		// 	if (word)
		// 	{
		// 		char *tmp = word;
		// 		word = ft_strjoin(word, expansion, "");
		// 		ft_strdel(&tmp);
		// 		ft_strdel((char **)&expansion);
		// 		if (!word)
		// 			return NULL;
		// 	}
		// 	else
		// 		word = (char *)expansion;

		// 	// reset start_idx to the pos after the EXP_PARAM
		// 	start_idx = lexer->pos;
		// }
		// else
		advance_lexer(lexer);
	}

	if (start_idx != lexer->pos)
	{
		word = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
		// char *tmp = word;
		// char *queue_word = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
		// word = ft_strjoin(word, queue_word, "");
		// ft_strdel(&tmp);
		// ft_strdel(&queue_word);
	}

	(void)shell;
	fprintf(stderr, "word = %s\n", word);

	return (t_word_token){.text = word, .expansion = NULL};
}
