#ifndef SHELLMOD_RS_H
#define SHELLMOD_RS_H

#include "token.h"
#include "lexer.h"
#include "parser.h"

const char *hello_rust(void);
const t_btree *parser(const char *const c_char);

#endif
