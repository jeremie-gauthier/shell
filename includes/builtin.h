#ifndef BUILTIN_H
#define BUILTIN_H

#include "process.h"
#include "shell.h"
#include <stdbool.h>

bool builtin_exit(t_shell *const shell, const t_cmd command);

#endif
