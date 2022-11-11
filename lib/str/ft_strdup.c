#include "lib_mem.h"
#include "lib_str.h"
#include <stddef.h>

char *ft_strdup(const char *const s)
{
	char *sdup;
	size_t len;

	len = ft_strlen(s);
	if (!(sdup = ft_strnew(len)))
		return NULL;
	ft_memcpy(sdup, s, len);
	return sdup;
}
