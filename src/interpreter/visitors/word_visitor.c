#include "ast.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Transform a sequence of AST nodes into a 2D-array
 */
static char **get_command_argv(t_ast *node)
{
	t_ast *head = node;

	size_t argc = 0;
	while (node && node->token.type == Word)
	{
		node = node->right;
		argc++;
	}

	char **argv = malloc(sizeof(*argv) * argc);
	if (!argv)
		return NULL;

	node = head;
	size_t i = 0;
	while (i < argc)
	{
		argv[i] = (char *)node->token.value;
		node = node->right;
		i++;
	}

	return argv;
}

void word_visitor(t_ast *node)
{
	const char *command = node->token.value;
	char *const *argv = get_command_argv(node);

	execve(command, argv, NULL);
}
