#include "lib_ht.h"
#include "lib_str.h"
#include <stddef.h>
#include <stdio.h>

char *ht_get(t_ht *table, char *key)
{
	const size_t idx = ht_hash(key);
	const t_ht_item *item = table->items[idx];
	t_ht_lst *head = table->overflow_buckets[idx];

	while (HT_HAS(item))
	{
		if (ft_strcmp(item->key, key) == SAME_STR)
			return item->value;
		if (head == NULL)
			return NULL;
		item = head->item;
		head = head->next;
	}
	return NULL;
}
