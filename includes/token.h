#ifndef TOKEN_H
#define TOKEN_H

#define DEFAULT_TOKEN_LIST_CAPACITY 16
#define NB_DISTINCT_TOKENS End + 1

enum e_token_type
{
	Word = 0,
	Unknown,
	End,
};

typedef struct s_token
{
	const char *value;
	enum e_token_type type;
} t_token;

#endif
