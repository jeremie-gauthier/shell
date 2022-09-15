#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"

/*
 ** PARSER
 */

typedef struct s_parser
{
	t_lexer lexer;
	t_token current_token;
} t_parser;

t_parser create_parser(const t_lexer lexer);
bool eat(t_parser *const restrict parser, const enum e_token_type token_type);
t_ast *parse(t_parser *const restrict parser);

/*
 ** RULES
 */

t_ast *parse_cmd(t_parser *const restrict parser);

#endif
