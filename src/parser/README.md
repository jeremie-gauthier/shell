# Parser

The parser module is responsible to build an AST from a token list.

## Grammar

Tokens from enum `e_token_type` are our terminals, which are written in uppercase below for readability.

Rules (described in regex style):

```txt
factor: COMMAND

expr: factor (OPERATOR factor*)*
```

## Definition

```c
const t_btree const *parser(const *const lexer);
```

Where `t_btree` equals:

```c
typedef struct s_btree {
	struct s_btree *left;
	struct s_btree *right;
	void *data;
} t_btree;
```
