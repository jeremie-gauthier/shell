#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "parser.h"
#include <stdbool.h>

bool interpreter(t_parser *parser);

/*
 * * VISITORS
 */

void word_visitor(t_ast *node);

#endif
