#include <string.h>
#include "token.h"
#include "lexer.h"

t_token whitespace(t_lexer *const lexer)
{
	const size_t span = strspn(lexer->input, WHITESPACES) + 1;
	lexer->input_idx += span;
	return (t_token) { .type = Whitespace, .value = NULL };
}
