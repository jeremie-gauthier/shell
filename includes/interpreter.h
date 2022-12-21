#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "parser.h"
#include "process.h"
#include "shell.h"

int interpreter(t_shell *const shell, t_parser *parser);
bool subst_param_exps(t_shell *const shell, t_word_token *word);
bool subst_cmd_words(t_shell *const shell, t_command_token *command);

/*
 * * VISITORS
 */

void free_command(const t_cmd *command);
const t_cmd *get_command_from_token(t_command_token *token);

#endif
