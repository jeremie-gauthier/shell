#include "lexer.h"
#include "lib_char.h"
#include "lib_str.h"
#include "token.h"

t_token word(t_lexer *const restrict lexer)
{
	size_t idx = lexer->input_idx;

	while (lexer->input[idx] && ft_isalnum(lexer->input[idx]))
		idx++;

	const size_t size = idx - lexer->input_idx;
	const char *value = ft_strndup(&lexer->input[lexer->input_idx], size);

	lexer->input_idx = idx;
	return (t_token){.type = Word, .value = value};
}
