#ifndef TOKEN_H
#define TOKEN_H

#include "lib_vec.h"
#include "shell.h"
#include <stddef.h>

#define NB_DISTINCT_TOKENS End + 1
#define IS_VALID_TOKEN(token_got, token_expected) (token_got == token_expected)

enum e_token_type
{
	Unknown = 0,
	Word,
	Command,
	CommandSeparator,
	End,
};

enum e_expansion_type
{
	Parameter = 0,
	Tilde,
};

enum e_tilde_exp_type
{
	Literal = 0,
	Home,
	Pwd,
	Oldpwd,
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
	char *substitution;
	union
	{
		enum e_tilde_exp_type tilde_exp_type;
		// TODO: add param_exp_type
	};
	enum e_expansion_type type;
} t_expansion_token;

// token for word terminal
typedef struct s_word_token
{
	char *text;
	char *substitution;
	t_vec *expansions;
} t_word_token;

// token for command rule
typedef struct s_command_token
{
	/// @brief This is the name of the cmd to execute
	t_word_token *name;
	/// @brief This is the list of args
	t_vec *suffix;
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
		t_word_token *word;
		t_expansion_token *expansion;
		t_command_token *command;
		t_pipeline_token *pipeline;
	};
	enum e_token_type type;
} t_token;

/*
 ** DEBUG
 */
#ifdef DEBUG
void print_token(t_token token);
char *token_type_to_str(enum e_token_type type);
void print_param_exps_vec(void **item);
void print_word_vec(t_vec *word_vec);
#endif

#endif
