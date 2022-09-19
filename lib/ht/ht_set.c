#include "lib_ht.h"
#include "lib_str.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char *handle_collision(t_ht *table, size_t idx, t_ht_item *item)
{
	t_ht_lst *head = table->overflow_buckets[idx];

	if (head == NULL)
	{
		if (!(head = malloc(sizeof(*head))))
			return NULL;
		head->item = item;
		table->overflow_buckets[idx] = head;
		return item->value;
	}

	if (!(table->overflow_buckets[idx] = ht_lst_insert(head, item)))
		return NULL;
	return item->value;
}

const char *ht_set(t_ht *table, const char *key, const char *value)
{
	const size_t idx = ht_hash(key);

	t_ht_item *current_item = table->items[idx];
	if (HT_HAS_NOT(current_item))
	{
		if (table->count == table->size)
			return NULL;

		if (!(table->items[idx] = ht_create_item(key, value)))
			return NULL;
		table->count++;
		return value;
	}

	if (ft_strcmp(current_item->key, key) == SAME_STR)
	{
		char *new_value = ft_strdup(value);
		if (!new_value)
			return NULL;
		ft_strdel(&current_item->value);
		table->items[idx]->value = new_value;
		table->count++;
		return value;
	}

	t_ht_item *item = ht_create_item(key, value);
	if (!item)
		return NULL;
	return handle_collision(table, idx, item);
}
