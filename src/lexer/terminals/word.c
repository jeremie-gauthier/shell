#include "lexer.h"
#include "lib_char.h"
#include "lib_str.h"
#include "token.h"

const char *word(t_lexer *const restrict lexer)
{
	const size_t start_idx = lexer->pos;

	while (lexer->current_char && ft_isgraph(lexer->current_char))
		advance_lexer(lexer);

	return ft_strndup(&lexer->input[start_idx], lexer->pos - start_idx);
}
