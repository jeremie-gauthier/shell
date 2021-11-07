#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"
#include "libft.h"

const t_token *lexer(const char *str)
{
	const size_t nb_words = count_words(str, WHITESPACES);
	t_token *tokens = malloc(sizeof(t_token) * (nb_words + 1));
	if (tokens == NULL)
		return (NULL);

	char *token = strtok((char *)str, WHITESPACES);
	size_t i = 0;
	while (token != NULL)
	{
		t_token new_token = {
			.value = token,
			.type = Word,
		};
		tokens[i++] = new_token;
		token = strtok(NULL, WHITESPACES);
	}
	tokens[i].type = End;
	tokens[i].value = NULL;
	return tokens;
}
