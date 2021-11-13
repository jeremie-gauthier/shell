# Lexer

The lexer module is responsible to split a string into recognizable tokens.

## Definition

```c
t_lexer lexer(const char *str);
```

Where `t_lexer` equals:

```c
typedef struct s_lexer
{
	const char *input; // the user input
	t_token *tokens; // the list of tokens formed by parsing the input
	size_t tokens_len; // the tokens list length
	size_t tokens_cap; // the tokens list memory capacity
	size_t input_idx; // the current parsing index for the input
	bool has_error; // if the lexer ended prematurily due to some kind of error
} t_lexer;
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
	Whitespace = 0,
	Command,
	Operator, // generic operator type for lexer
	Redirection, // is a specific operator
	Pipe, // is a specific operator
	Separator, // is a specific operator
	Logical, // is a specific operator
	Number,
	Unknown,
	... // and more
	End, // <= Terminates by End, as End is used in a #define to know how many types are defined
};```
