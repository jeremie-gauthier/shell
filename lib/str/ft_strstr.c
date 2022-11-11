#include "lib_str.h"
#include <stddef.h>

char *ft_strstr(const char *haystack, const char *const needle)
{
	size_t len_needle;
	int cmp;

	if (*needle == '\0')
		return (char *)haystack;
	len_needle = ft_strlen(needle);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			cmp = ft_strncmp(haystack, needle, len_needle);
			if (cmp == SAME_STR)
				return (char *)haystack;
		}
		haystack++;
	}
	return NULL;
}
