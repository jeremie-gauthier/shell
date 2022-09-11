# Parser

The parser uses the first components of the tokens produced by the lexical analyzer to create an abstract syntax tree (AST) representation that depicts the grammatical structure of the token stream.

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
