#include "ast.h"
#include "lib_str.h"
#include "process.h"
#include "token.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Transform a sequence of AST nodes into a 2D-array
 */
static char **get_command_argv(t_ast *node, size_t *argc)
{
	t_ast *head = node;

	*argc = 0;
	while (node && node->token.type == Word)
	{
		node = node->right;
		(*argc)++;
	}
	if (*argc == 0)
		return NULL;

	char **argv = malloc(sizeof(*argv) * (*argc + 1));
	if (!argv)
		return NULL;

	node = head;
	size_t i = 0;
	while (i < *argc)
	{
		argv[i] = (char *)node->token.value;
		node = node->right;
		i++;
	}
	argv[i] = NULL;

	return argv;
}

/*
 *	If the command contains no slashes:
 *		- If the command is a shell function, that function is called.
 *		- Otherwise, if it corresponds to a built-in command, that command is used.
 *		- Otherwise, the shell searches $PATH for an executable with that name and executes it if found.
 *	If the command contains slashes, that named file is executed.
 */
void command_finder(t_token *cmd_tok)
{
	if (ft_strchr(cmd_tok->value, '/'))
	{
		cmd_tok->type = File;
		return;
	}

	if (ft_strcmp(cmd_tok->value, "exit") == SAME_STR || ft_strcmp(cmd_tok->value, "echo") == SAME_STR)
	{
		cmd_tok->type = BuiltInCommand;
		return;
	}

	cmd_tok->type = PathCommand;
}

t_cmd word_visitor(t_ast *node)
{
	size_t argc;
	const char *path = node->token.value;
	char *const *argv = get_command_argv(node, &argc);
	command_finder(&node->token);

	return create_command(path, argv, argc, node->token.type);
}
