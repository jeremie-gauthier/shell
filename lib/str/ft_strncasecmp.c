#include "lib_char.h"
#include "lib_str.h"
#include <stddef.h>

int ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			if (ft_tolower(*s1) != *s2 && ft_toupper(*s1) != *s2)
				return (unsigned char)*s1 - (unsigned char)*s2;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return SAME_STR;
	return (unsigned char)*s1 - (unsigned char)*s2;
}
