#include "lib_ht.h"
#include <stddef.h>
#include <stdio.h>

void print_search(t_ht *table, char *key)
{
	char *val;
	if ((val = ht_get(table, key)) == NULL)
	{
		printf("Key:%s does not exist\n", key);
		return;
	}
	else
	{
		printf("Key:%s, Value:%s\n", key, val);
	}
}

void print_table(t_ht *table)
{
	printf("\n-------------------\n");
	for (size_t i = 0; i < table->size; i++)
	{
		if (table->items[i])
		{
			printf("Index:%zu, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->data);
			if (table->overflow_buckets[i])
			{
				printf(" => Overflow Bucket => ");
				t_ht_lst *head = table->overflow_buckets[i];
				while (head)
				{
					printf("Key:%s, Value:%s ", head->item->key, head->item->data);
					head = head->next;
				}
			}
			printf("\n");
		}
	}
	printf("-------------------\n");
}
