#include "lib_str.h"
#include <stdio.h>

// @enum SimpleSubstitution
const char *simple_subst(const char *const subst, const char *const _)
{
	(void)_;

	if (subst)
		return ft_strdup(subst);
	return NULL;
}
