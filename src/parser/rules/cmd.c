#include "ast.h"
#include "lib_arr.h"
#include "lib_mem.h"
#include "lib_str.h"
#include "parser.h"
#include "process.h"
#include "shell.h"
#include <stdlib.h>

// const t_cmd *create_cmd(int argc, const char **argv)
// {
// 	t_cmd *cmd = malloc(sizeof(*cmd));
// 	if (!cmd)
// 		return NULL;

// 	cmd->argc = argc;
// 	cmd->argv = argv;
// 	return cmd;
// }

// It will creates a reduction token called Command Token
// from all the Word Token it has parsed.
t_ast *parse_cmd(const t_shell *const shell, t_parser *const parser)
{
	const t_token current_token = parser->current_token;
	if (IS_VALID_TOKEN(current_token.type, Word))
		eat(shell, parser, Word);

	t_command_token cmd = {.name = current_token.word,
						   .suffix = NULL};

	while (IS_VALID_TOKEN(parser->current_token.type, Word))
	{
		if (cmd->suffix == NULL)
			cmd->suffix = vec_create(1);
		vec_push(cmd->suffix, parser->current_token.word);
		eat(shell, parser, Word);
	}

	const t_token cmd_token = {.type = Command, .command = cmd};
	return AST_CREATE_ONE(cmd_token);
}
