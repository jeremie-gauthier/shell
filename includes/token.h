#ifndef TOKEN_H
#define TOKEN_H

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

/*
 ** DEBUG
 */
void print_token(const t_token token);
const char *token_type_to_str(const enum e_token_type type);

#endif
