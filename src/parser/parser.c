#include "parser.h"
#include "lexer.h"

t_parser create_parser(const t_lexer lexer)
{
	t_token token = get_next_token((t_lexer *)&lexer);
	t_parser parser = {
		.lexer = lexer,
		.current_token = token,
	};

	return parser;
}
