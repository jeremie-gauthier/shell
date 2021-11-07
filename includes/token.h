#ifndef TOKEN_H
#define TOKEN_H

enum e_token_type
{
	Word = 0,
	Operator,
	End,
};

typedef struct s_token
{
	const char *value;
	enum e_token_type type;
} t_token;

typedef struct s_lexer
{
	const char *input;
	size_t idx;
} t_lexer;

#endif
