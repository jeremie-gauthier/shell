#include "lexer.h"
#include "lib_str.h"
#include "token.h"

t_token whitespace(t_lexer *const restrict lexer)
{
	const size_t span = ft_strspn(lexer->input, WHITESPACES) + 1;
	lexer->input_idx += span;
	return (t_token){.type = Whitespace, .value = NULL};
}
