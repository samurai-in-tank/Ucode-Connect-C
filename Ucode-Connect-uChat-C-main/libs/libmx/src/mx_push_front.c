#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
	if (!data || !list) {
		return;
	}
	t_list *new = mx_create_node(data);
	if (!new) {
		return;
	}
	new->next = *list;
	*list = new;
}
