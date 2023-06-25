#include "lib_str.h"

// @enum UseDefaultValueIfNone
const char *param_default_subst(const char *const subst, const char *const alt)
{
	if (!subst)
		return NULL;

	if (alt)
		return ft_strdup(alt);

	return NULL;
}
