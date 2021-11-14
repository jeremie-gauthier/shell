#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"

#define BTREE_CREATE_ONE(token) btree_create_node(token, NULL, NULL)

/*
 ** BINARY TREE
 */
typedef struct s_btree {
	struct s_btree *left;
	struct s_btree *right;
	t_token token;
} t_btree;

t_btree *btree_create_node(t_token token, const t_btree *left, const t_btree *right);
void btree_apply_prefix(t_btree *btree, void (*fn)(t_token));
void btree_free(t_btree *btree);

/*
 ** PARSER
 */
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
