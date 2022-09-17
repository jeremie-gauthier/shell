#include "lib_ht.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stdlib.h>

t_ht_lst *ht_lst_insert(t_ht_lst *list, t_ht_item *item)
{
	t_ht_lst *node = malloc(sizeof(*list));
	if (!node)
		return NULL;
	node->item = item;
	node->next = NULL;

	if (!list)
		return node;

	if (list->next == NULL)
	{
		list->next = node;
		return list;
	}

	t_ht_lst *temp = list;
	while (temp->next->next)
		temp = temp->next;

	temp->next = node;
	return list;
}

t_ht_item *ht_lst_remove(t_ht_lst *list)
{
	// Removes the head from the linked list
	// and returns the item of the popped element
	if (!list || !list->next)
		return NULL;

	t_ht_lst *node = list->next;
	t_ht_lst *temp = list;
	temp->next = NULL;
	list = node;
	t_ht_item *it = NULL;
	ft_memcpy(temp->item, it, sizeof(*it));
	ht_item_free(temp->item);
	ft_memdel((void **)&temp);
	return it;
}

void ht_lst_free(t_ht_lst *list)
{
	t_ht_lst *temp = list;
	while (list)
	{
		temp = list;
		list = list->next;
		ht_item_free(temp->item);
		ft_memdel((void **)&temp);
	}
}