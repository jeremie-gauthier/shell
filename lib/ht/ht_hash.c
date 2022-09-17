#include "lib_ht.h"
#include <stddef.h>

size_t ht_hash(char *str)
{
	size_t i = 0;
	for (size_t j = 0; str[j]; j++)
		i += str[j];
	return i % HT_CAPACITY;
}
