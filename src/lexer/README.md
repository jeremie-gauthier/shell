# Lexer

The **lexical analyzer** (lexer) reads the stream of characters making up the source program and groups the characters into meaningful sequences called **lexemes**.
For each lexeme, the lexical analyzer produces as output a **token** of the form below that it passes on to the subsequent phase, [syntax analysis](../parser/README.md).

## Shell grammar

### Terminals

```txt
WORD: 		string of alphanumeric chars
PIPE: 		|
SEPARATOR: 	;
LOGICAL_OR:	||
LOGICAL_AND:	&&
REDIRECTION: <<, <, >, >>, &> (get the name of each and create separate tokens)
```

### Rules

_arg_: WORD
_cmd_: _arg_<sup>+</sup>
_expr_: _cmd_ ( _operator_<sup>+</sup> _cmd_<sup>?</sup> )<sup>\*</sup>
_operator_: _redirection_ | PIPE | _logical_ | SEPARATOR
_redirection_: < | << | > | >> | &>
_logical_: LOGICAL_OR | LOGICAL_AND

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
	Word,
	Operator, // generic operator type for lexer
	Redirection, // is a specific operator
	Pipe, // is a specific operator
	Separator, // is a specific operator
	Logical, // is a specific operator
	Number,
	Unknown,
	... // and more
	End, // <= Terminates by End, as End is used in a #define to know how many types are defined
};
```
