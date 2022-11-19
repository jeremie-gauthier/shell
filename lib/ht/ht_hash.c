#include "lib_ht.h"
#include <stddef.h>

size_t ht_hash(const char *str)
{
	size_t i = 0;
	for (size_t j = 0; str[j]; j++)
	{
		const size_t c = (size_t)str[j];
		i += c * ((i ^ c) + j);
	}
	return i % HT_CAPACITY;
}
