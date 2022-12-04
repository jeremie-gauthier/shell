#ifndef TOKEN_H
#define TOKEN_H

#define NB_DISTINCT_TOKENS End + 1
#define IS_VALID_TOKEN(token_got, token_expected) (token_got == token_expected)

enum e_token_type
{
	Unknown = 0,
	Word,
	Command,
	BuiltInCommand,
	PathCommand,
	File,
	CommandSeparator,
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
