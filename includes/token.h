#ifndef TOKEN_H
#define TOKEN_H

#define NB_DISTINCT_TOKENS End + 1
#define IS_VALID_TOKEN(token, valid_token_mask) ((token & valid_token_mask) == token)

enum e_token_type
{
	Unknown = 0,
	Word = 1 << 0,
	BuiltInCommand = 1 << 1,
	PathCommand = 1 << 2,
	File = 1 << 3,
	CommandSeparator = 1 << 4,
	End = 1 << 5,
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
