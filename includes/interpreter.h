#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "parser.h"
#include "process.h"
#include "shell.h"

int interpreter(t_shell *const shell, t_parser *parser);

/*
 * * VISITORS
 */

void free_command(const t_cmd *command);
const t_cmd *get_command_from_token(t_command_token *token);

#endif
