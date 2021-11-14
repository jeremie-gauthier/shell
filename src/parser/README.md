# Parser

The parser module is responsible to build an AST from a token list.

## Grammar

Tokens from enum `e_token_type` are our terminals, which are written in uppercase below for readability.

Rules (described in regex style):

```txt
factor: COMMAND
<!-- A factor is a command -->

expr: factor (OPERATOR factor?)*
<!-- An expr is a factor, optionally followed by an OPERATOR which is optionally followed by another factor. -->
<!-- The whole optional part is repeated 0 to N times. -->
```

## Definition

```c
const t_btree *parse(const t_lexer *const lexer);
```

Where `t_btree` equals:

```c
typedef struct s_btree {
	struct s_btree *left;
	struct s_btree *right;
	t_token token;
} t_btree;
```
