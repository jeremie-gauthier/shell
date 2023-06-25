#include "lib_str.h"
#include <stdio.h>

// TODO: use param_simple_subst to avoid code duplication
// @enum SubstitutionStringLength
const char *param_length_subst(const char *const subst)
{
	const size_t length = subst ? ft_strlen(subst) : 0;
	char *buf = ft_strnew(20);
	if (!buf)
		return NULL;

	sprintf(buf, "%zu", length);
	return buf;
}
