#include "ast.h"
#include "lib_str.h"
#include "process.h"
#include "token.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

// /*
//  * Transform a sequence of AST nodes into a 2D-array
//  */
// static char **get_command_argv(t_ast *node, size_t *argc)
// {
// 	t_ast *head = node;

// 	*argc = 0;
// 	while (node && node->token.type == Word)
// 	{
// 		node = node->right;
// 		(*argc)++;
// 	}
// 	if (*argc == 0)
// 		return NULL;

// 	char **argv = malloc(sizeof(*argv) * (*argc + 1));
// 	if (!argv)
// 		return NULL;

// 	node = head;
// 	size_t i = 0;
// 	while (i < *argc)
// 	{
// 		argv[i] = (char *)node->token.data;
// 		node = node->right;
// 		i++;
// 	}
// 	argv[i] = NULL;

// 	return argv;
// }

/*
 *	If the command contains no slashes:
 *		- If the command is a shell function, that function is called.
 *		- Otherwise, if it corresponds to a built-in command, that command is used.
 *		- Otherwise, the shell searches $PATH for an executable with that name and executes it if found.
 *	If the command contains slashes, that named file is executed.
 */
void command_finder(t_token *cmd_tok)
{
	if (ft_strchr(cmd_tok->command.name->text, '/'))
	{
		cmd_tok->type = File;
		return;
	}

	if (
		ft_strcmp(cmd_tok->command.name->text, "exit") == SAME_STR ||
		ft_strcmp(cmd_tok->command.name->text, "echo") == SAME_STR ||
		ft_strcmp(cmd_tok->command.name->text, "env") == SAME_STR ||
		ft_strcmp(cmd_tok->command.name->text, "unsetenv") == SAME_STR ||
		ft_strcmp(cmd_tok->command.name->text, "setenv") == SAME_STR ||
		ft_strcmp(cmd_tok->command.name->text, "cd") == SAME_STR)
	{
		cmd_tok->type = BuiltInCommand;
		return;
	}

	cmd_tok->type = PathCommand;
}

t_cmd word_visitor(t_ast *node)
{
	// size_t argc;
	const char *path = node->token.command.name->text;
	// char *const *argv = get_command_argv(node, &argc);
	// char *const *argv = node->token.command.suffix;
	command_finder(&node->token);

	// return create_command(path, argv, argc, node->token.type);
	return (t_cmd){.argc = 0, .argv = NULL, .path = path, .type = BuiltInCommand};
}
