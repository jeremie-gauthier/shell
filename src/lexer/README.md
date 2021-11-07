# Lexer

The lexer module is responsible to split a string into recognizable tokens.

## Definition

```c
const t_token *lexer(const char *str)
```

Where `t_token` equals:

```c
typedef struct s_token
{
	char *value;
	enum e_token_type type;
} t_token;
```

Where `e_token_type` equals:

```c
enum e_token_type
{
	Word = 0,
	Operator,
};
```
