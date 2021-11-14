#ifndef PARSER_H
#define PARSER_H

#include "btree.h"
#include "lexer.h"

typedef struct s_parser {
	const t_lexer *const lexer;
	size_t current_token;
} t_parser;

const t_btree *parse(const t_lexer *const lexer);
t_token get_current_token(const t_parser *const parser);
bool eat(t_parser *const parser, const enum e_token_type type);

/*
 ** RULES
 */
t_btree *expr(t_parser *parser);
t_btree *factor(t_parser *parser);

/*
 ** DEBUG
 */
void print_btree(t_btree *root);

#endif
