#include <stddef.h>

char *ft_strrchr(const char *str, int c)
{
	const char *rchr = NULL;

	rchr = NULL;
	while (*str)
	{
		if (*str == c)
			rchr = str;
		str++;
	}
	if (*str == c)
		return (char *)str;
	return (char *)rchr;
}
