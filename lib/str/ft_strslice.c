#include "lib_mem.h"
#include "lib_str.h"
#include <stddef.h>

char *ft_strslice(const char *restrict str, const size_t start, const size_t len)
{
	char *dst;

	if (!str || !len)
		return NULL;
	if (!(dst = ft_strnew(len)))
		return NULL;
	ft_memcpy(dst, str + start, len);
	return dst;
}
