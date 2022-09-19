#include "lib_ht.h"
#include "lib_str.h"
#include <stdbool.h>
#include <stddef.h>

bool ht_delete(t_ht *table, const char *key)
{
	const size_t idx = ht_hash(key);
	t_ht_item *item = table->items[idx];
	t_ht_lst *head = table->overflow_buckets[idx];

	if (HT_HAS_NOT(item))
		return false;

	if (head == NULL && ft_strcmp(item->key, key) == SAME_STR)
	{
		// No collision chain. Remove the item
		// and set table index to NULL
		table->items[idx] = NULL;
		ht_item_free(item);
		table->count--;
		return true;
	}

	if (head != NULL)
	{
		// Collision Chain exists
		if (ft_strcmp(item->key, key) == SAME_STR)
		{
			// Remove this item and set the head of the list
			// as the new item
			ht_item_free(item);
			t_ht_lst *node = head;
			head = head->next;
			node->next = NULL;
			table->items[idx] = ht_create_item(node->item->key, node->item->value);
			ht_lst_free(node);
			table->overflow_buckets[idx] = head;
			return true;
		}

		t_ht_lst *curr = head;
		t_ht_lst *prev = NULL;
		while (curr)
		{
			if (ft_strcmp(curr->item->key, key) == SAME_STR)
			{
				if (prev == NULL)
				{
					// First element of the chain. Remove the chain
					ht_lst_free(head);
					table->overflow_buckets[idx] = NULL;
					return true;
				}
				else
				{
					// This is somewhere in the chain
					prev->next = curr->next;
					curr->next = NULL;
					ht_lst_free(curr);
					table->overflow_buckets[idx] = head;
					return true;
				}
			}
			curr = curr->next;
			prev = curr;
		}
	}

	return false;
}
