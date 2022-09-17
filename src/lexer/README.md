# Lexer

The **lexical analyzer** (lexer) reads the stream of characters making up the source program and groups the characters into meaningful sequences called **lexemes**.
For each lexeme, the lexical analyzer produces as output a **token** of the form below that it passes on to the subsequent phase, [syntax analysis](../parser/README.md).

For a good lexer tutorial, follow this guide: https://ruslanspivak.com/lsbasi-part1/

## Shell grammar

### Terminals

```txt
WORD:	string of graphical chars
```

### Rules

_arg_: WORD
_cmd_: _arg_<sup>+</sup>
_expr_: _cmd_ ( _operator_<sup>+</sup> _cmd_<sup>?</sup> )<sup>\*</sup>

## Definition

```c
t_lexer create_lexer(const char *const restrict str);
```

Where `t_lexer` equals:

```c
typedef struct s_lexer
{
	const char *input; // input from the user
	size_t pos; // current position in the input
	char current_char; // current char in the input
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
	Word = 0,
	Unknown,
	End, // <= Terminates by End, as End is used in a #define to know how many types are defined
};
```
