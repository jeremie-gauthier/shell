#include "lib_str.h"
#include <stddef.h>

char *ft_strjoin(char const *const restrict s1, char const *const restrict s2)
{
	char *str;
	size_t len_s1;

	if (!s1 && !s2)
		return NULL;
	if ((!s1 && s2) || (s1 && !s2))
		return ft_strdup(s1 ? s1 : s2);
	len_s1 = ft_strlen(s1);
	if (!(str = ft_strnew(len_s1 + ft_strlen(s2))))
		return NULL;
	ft_strcpy(str, s1);
	ft_strcpy(str + len_s1, s2);
	return str;
}
