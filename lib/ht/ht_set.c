#include "lib_ht.h"
#include "lib_str.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool handle_collision(t_ht *table, size_t idx, t_ht_item *item)
{
	t_ht_lst *head = table->overflow_buckets[idx];

	if (head == NULL)
	{
		if (!(head = malloc(sizeof(*head))))
			return false;
		head->item = item;
		table->overflow_buckets[idx] = head;
		return true;
	}

	if (!(table->overflow_buckets[idx] = ht_lst_insert(head, item)))
		return false;
	return true;
}

bool ht_set(t_ht *table, char *key, char *value)
{
	const size_t idx = ht_hash(key);

	t_ht_item *current_item = table->items[idx];
	if (HT_HAS_NOT(current_item))
	{
		if (table->count == table->size)
			return false;

		if (!(table->items[idx] = ht_create_item(key, value)))
			return false;
		table->count++;
		return true;
	}

	if (ft_strcmp(current_item->key, key) == SAME_STR)
	{
		char *new_value = ft_strdup(value);
		if (!new_value)
			return false;
		ft_strdel(&current_item->value);
		table->items[idx]->value = new_value;
		table->count++;
		return true;
	}

	t_ht_item *item = ht_create_item(key, value);
	if (!item)
		return false;
	return handle_collision(table, idx, item);
}
