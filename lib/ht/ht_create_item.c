#include "lib_ht.h"
#include "lib_str.h"
#include <stdlib.h>

t_ht_item *ht_create_item(const char *key, const char *value)
{
	t_ht_item *item = malloc((sizeof *item));
	if (!item)
		return NULL;

	item->key = ft_strdup(key);
	item->value = ft_strdup(value);
	return item;
}
