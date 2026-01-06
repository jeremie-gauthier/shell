#include "lib_str.h"

// @enum UseAlternativeValueIfNone
const char *param_alt_subst(const char *const subst, const char *const alt)
{
	if (subst)
		return ft_strdup(subst);

	if (alt)
		return ft_strdup(alt);

	return NULL;
}
