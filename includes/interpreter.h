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

t_cmd word_visitor(t_ast *node);

#endif
