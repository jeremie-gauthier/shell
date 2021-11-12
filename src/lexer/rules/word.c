#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexer.h"

t_token word(t_lexer *const lexer)
{
	size_t idx = lexer->input_idx;

	while (lexer->input[idx] && isalnum(lexer->input[idx]))
		idx++;

	const size_t size = idx - lexer->input_idx;
	const char *value = strndup(&lexer->input[lexer->input_idx], size);

	lexer->input_idx = idx;
	return (t_token) { .type = Word, .value = value };
}
