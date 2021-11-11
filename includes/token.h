#ifndef TOKEN_H
#define TOKEN_H

#define DEFAULT_TOKEN_LIST_CAPACITY 16

enum e_token_type
{
	Whitespace = 0,
	Word,
	Operator,
	Number,
	End,
	Unknown
};

typedef struct s_token
{
	const char *value;
	enum e_token_type type;
} t_token;

#endif
