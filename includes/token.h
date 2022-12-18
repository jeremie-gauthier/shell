#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

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

// locate a substring in a string
typedef struct s_loc
{
	size_t start;
	size_t end;
} t_loc;

// token for shell expansion parameters
typedef struct s_expansion_token
{
	t_loc loc;
	char *parameter;
} t_expansion_token;

// token for word terminal
typedef struct s_word_token
{
	char *text;
	t_expansion_token *expansion;
} t_word_token;

// token for command rule
typedef struct s_command_token
{
	t_word_token name;
	t_word_token *suffix;
} t_command_token;

// token for pipeline rule
typedef struct s_pipeline_token
{
	t_command_token *commands;
} t_pipeline_token;

// generic token used in the AST
typedef struct s_token
{
	union
	{
		t_word_token word;
		t_expansion_token expansion;
		t_command_token command;
		t_pipeline_token pipeline;
	};
	enum e_token_type type;
} t_token;

/*
 ** DEBUG
 */
void print_token(t_token token);
char *token_type_to_str(enum e_token_type type);

#endif
