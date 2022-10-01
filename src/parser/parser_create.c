#include "lexer.h"
#include "parser.h"
#include "token.h"

t_parser parser_create(const t_shell *const shell, const t_lexer lexer)
{
	t_token token = get_next_token(shell, (t_lexer *)&lexer);
	t_parser parser = {
		.lexer = lexer,
		.current_token = token,
	};

	return parser;
}
