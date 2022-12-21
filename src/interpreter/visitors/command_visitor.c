#include "ast.h"
#include "lib_arr.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "lib_vec.h"
#include "process.h"
#include "token.h"
#include <stdlib.h>

#include <stdio.h>

void free_command(const t_cmd *command)
{
	ft_strdel((char **)&command->path);
	if (command->argv)
		ft_arr_free(command->argv, command->argc);
	ft_memdel((void **)&command);
}

static t_cmd *create_command()
{
	t_cmd *command = malloc(sizeof(*command));
	if (!command)
		return NULL;
	ft_bzero(command, sizeof(*command));
	return command;
}

static char **get_argv_from_vec(const char *const arg0, t_vec *vec)
{
	size_t size = (vec ? vec->size : 0) + 1;
	char **argv = malloc(sizeof(*argv) * (size + 1));
	if (!argv)
		return NULL;

	argv[0] = ft_strdup(arg0);
	if (vec)
		for (size_t i = 0; i < vec->size; i++)
		{
			t_word_token *word = vec->items[i];
			char *command_arg = word->substitution ? word->substitution : word->text;
			argv[i + 1] = ft_strdup(command_arg);
		}
	argv[size + 1] = NULL;
	return argv;
}

/*
 *	If the command contains no slashes:
 *		- If the command is a shell function, that function is called.
 *		- Otherwise, if it corresponds to a built-in command, that command is used.
 *		- Otherwise, the shell searches $PATH for an executable with that name and executes it if found.
 *	If the command contains slashes, that named file is executed.
 */
static enum e_command_type get_command_type(const char *const path)
{
	if (ft_strchr(path, '/'))
		return File;

	if (
		ft_strcmp(path, "exit") == SAME_STR ||
		ft_strcmp(path, "echo") == SAME_STR ||
		ft_strcmp(path, "env") == SAME_STR ||
		ft_strcmp(path, "unsetenv") == SAME_STR ||
		ft_strcmp(path, "setenv") == SAME_STR ||
		ft_strcmp(path, "cd") == SAME_STR)
		return BuiltIn;

	return Path;
}

/// @brief Create a t_cmd struct from a lexical token.
/// All expansions are also resolved during the process.
/// @param token A lexical token
/// @return A reference to a t_cmd struct
const t_cmd *get_command_from_token(t_command_token *token)
{
	t_cmd *command = create_command();
	if (!command)
		return NULL;

	char *command_path = token->name->substitution ? token->name->substitution : token->name->text;
	command->path = ft_strdup(command_path);
	command->type = get_command_type(command_path);
	command->argv = get_argv_from_vec(command_path, token->suffix);
	command->argc = 1 + (token->suffix ? token->suffix->size : 0);
	return command;
}
