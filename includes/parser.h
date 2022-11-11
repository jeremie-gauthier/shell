#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "shell.h"
#include "token.h"

/*
 ** PARSER
 */

typedef struct s_parser
{
	t_lexer lexer;
	t_token current_token;
} t_parser;

t_parser parser_create(const t_shell *const shell, const t_lexer lexer);
t_ast *parser_run(const t_shell *const shell, t_parser *const parser);
bool eat(const t_shell *const shell, t_parser *const parser, const enum e_token_type token_type);

/*
 ** RULES
 */

t_ast *parse_cmd(const t_shell *const shell, t_parser *const parser);

#endif
