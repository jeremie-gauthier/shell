#ifndef ENV_H
#define ENV_H

#include "lib_ht.h"
#include <stdbool.h>

char *env_get_value(char **env, char *key);
bool load_env_to_cache(t_ht *cache, char **env);
bool env_var_name_validate(const char *var);

#endif
