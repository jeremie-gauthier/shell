#include <stddef.h>
#include <string.h>

size_t count_words(const char *str, const char *const delimiters)
{
	size_t words = 0;

	while (*str)
	{
		const char *next_delimiter = strpbrk(str, (const char *)delimiters);
		if (next_delimiter == NULL)
			return words + 1;
		if (next_delimiter != str)
			words++;
		str = next_delimiter + strspn(next_delimiter, delimiters);
	}
	return (words);
}
