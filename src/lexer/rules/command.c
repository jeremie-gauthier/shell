#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexer.h"

t_token command(t_lexer *const lexer)
{
	size_t idx = lexer->input_idx;

	while (lexer->input[idx]
		&& ((isgraph(lexer->input[idx]) && !strchr(OPERATORS, lexer->input[idx]))
			|| isspace(lexer->input[idx])))
		idx++;

	const size_t size = idx - lexer->input_idx;
	const char *value = strndup(&lexer->input[lexer->input_idx], size);

	lexer->input_idx = idx;
	return (t_token) { .type = Command, .value = value };
}
