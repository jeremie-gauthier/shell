#include "lib_str.h"

// TODO: use param_simple_subst to avoid code duplication
// @enum ThrowErrorIfNone
const char *param_guard_subst(const char *const subst, const char *const alt)
{
	(void)alt;

	if (subst)
		return ft_strdup(subst);

	// TODO: print alt & exit

	return NULL;
}
