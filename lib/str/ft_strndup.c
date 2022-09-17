#include "lib_str.h"
#include <stddef.h>

char *ft_strndup(const char *const restrict src, size_t n)
{
	char *src_dup;

	if (!(src_dup = ft_strnew(n)))
		return NULL;
	ft_strncpy(src_dup, src, n);
	src_dup[n] = '\0';
	return src_dup;
}
