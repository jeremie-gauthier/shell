#include "lib_char.h"

int ft_isalnum(const int c)
{
	return ft_isalpha(c) || ft_isdigit(c);
}
