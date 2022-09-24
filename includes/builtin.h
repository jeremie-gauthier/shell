#ifndef BUILTIN_H
#define BUILTIN_H

#include "process.h"
#include "shell.h"

int builtin_exit(t_shell *const shell, const t_cmd command);
int builtin_echo(t_shell *const shell, const t_cmd command);

#endif
