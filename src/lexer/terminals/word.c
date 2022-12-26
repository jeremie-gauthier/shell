#include "lexer.h"
#include "lib_char.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "lib_vec.h"
#include "shell.h"
#include "token.h"
#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#ifdef DEBUG
void print_word_vec(t_vec *word_vec)
{
	for (size_t i = 0; i < word_vec->size; i++)
	{
		const t_word_token *word_tok = word_vec->items[i];
		printf("-> arg \"%s\"\n", word_tok->text);
		if (word_tok->expansions)
			vec_iter(word_tok->expansions, print_param_exps_vec);
	}
}
#endif

t_word_token *word(t_lexer *const lexer)
{
	t_word_token *token = malloc(sizeof(*token));
	ft_bzero(token, sizeof(*token));
	if (!token)
		return NULL;

	size_t start_idx = lexer->pos;

	while (lexer->current_char && ft_isgraph(lexer->current_char) && lexer->current_char != COMMAND_SEPARATOR)
	{
		if (lexer->current_char == EXP_PARAM_CHAR || lexer->current_char == EXP_TILDE_CHAR)
		{
			t_expansion_token *exp_param = parse_expansion(lexer);
			// set contextual param position
			exp_param->loc.start -= start_idx;
			exp_param->loc.end -= start_idx;

			if (!token->expansions)
				token->expansions = vec_create(1);
			vec_push(token->expansions, exp_param);
		}
		else
			advance_lexer(lexer);
	}

	if (start_idx != lexer->pos)
		token->text = ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);

	return token;
}
