#ifndef ENV_H
#define ENV_H

#include "lib_ht.h"
#include <stdbool.h>

#define IS_ENV_SET(var) (var >= 0)

char *env_get(char **env, const char *const key);
int env_get_idx(char **env, const char *const key);
char *env_set(char **env, const char *const key, const char *const value);
bool load_env_to_cache(t_ht *cache, char **env);
bool env_var_name_validate(const char *var);

#endif
