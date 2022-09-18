#include "lib_ht.h"
#include <stdlib.h>

t_ht_item *ht_create_item(char *key, char *value)
{
	t_ht_item *item = malloc((sizeof *item));
	if (!item)
		return NULL;

	item->key = key;
	item->value = value;
	return item;
}
