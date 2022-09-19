#include "lib_str.h"
#include <stddef.h>

char *ft_strjoin(const char *const restrict s1, const char *const restrict s2, const char *const restrict junction)
{
	char *str;

	if (!s1 && !s2)
		return NULL;
	if ((!s1 && s2) || (s1 && !s2))
		return ft_strdup(s1 ? s1 : s2);
	const size_t len_s1 = ft_strlen(s1);
	const size_t len_junction = ft_strlen(junction);
	if (!(str = ft_strnew(len_s1 + len_junction + ft_strlen(s2))))
		return NULL;
	ft_strcpy(str, s1);
	ft_strcpy(str + len_s1, junction);
	ft_strcpy(str + len_s1 + len_junction, s2);
	return str;
}
