#include "lib_char.h"
#include "lib_str.h"
#include <limits.h>

static int char_to_digit(const char c, const int base)
{
	if (c >= '0' && c <= '9')
		return c - '0';

	const char chr = (char)ft_toupper(c);
	const char max_base_char = (char)('A' + base - 10);
	if (chr >= 'A' && chr <= max_base_char)
		return chr - 'A' + 10;
	return -1;
}

static int parse_sign(const char **nptr)
{
	int isneg = 0;
	if (**nptr == '-')
		isneg = 1;
	if (**nptr == '-' || **nptr == '+')
		*nptr += 1;
	return isneg;
}

static int parse_base(const char **nptr, const int base)
{
	if ((base == 0 || base == 16) && ft_strncasecmp(*nptr, "0x", 2) == 0)
	{
		*nptr += 2;
		return 16;
	}
	if ((base == 0 || base == 8) && ft_strncmp(*nptr, "0", 1) == 0)
	{
		*nptr += 1;
		return 8;
	}
	if (base == 0)
		return 10;
	return base;
}

/*
 * The strtol() function converts the string in str to a long value.
 * The conversion is done according to the given base,
 *   which must be between 2 and 36 inclusive, or be the special value 0.
 */
long int ft_strtol(const char *nptr, char **endptr, int base)
{
	if (base < 0 || base == 1 || base > 36)
		return 0;

	while (*nptr && ft_isspace(*nptr))
		nptr++;

	int isneg = parse_sign(&nptr);
	base = parse_base(&nptr, base);

	long res = 0;
	int digit;
	while ((digit = char_to_digit(*nptr++, base)) >= 0)
	{
		const long tmp = res * base + digit;
		if (tmp < res)
		{
			if (endptr)
				*endptr = (char *)nptr;
			return LONG_MAX + isneg;
		}
		res = tmp;
	}
	if (endptr)
		*endptr = (char *)nptr;
	return isneg ? -res : res;
}