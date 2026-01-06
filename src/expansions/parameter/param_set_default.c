#include "token.h"

// @enum SetDefaultValueIfNone
const char *param_set_default(const char *const subst, const char *const alt)
{
	return param_alt_subst(subst, alt);
}
