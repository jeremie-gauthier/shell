#include "lexer.h"
#include "parser.h"
#include "token.h"

t_parser parser_create(const t_lexer lexer)
{
	t_token token = get_next_token((t_lexer *)&lexer);
	t_parser parser = {
		.lexer = lexer,
		.current_token = token,
	};

	return parser;
}
