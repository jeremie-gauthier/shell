#include <stddef.h>

char *ft_strchr(const char *str, int c)
{
	while (*str && c != *str)
		str++;

	if (*str == c)
		return (char *)str;
	return NULL;
}
