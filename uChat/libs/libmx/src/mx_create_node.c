#include "libmx.h"

t_list *mx_create_node(void *data) {
	if (!data) {
		return NULL;
	}
	t_list *new = (t_list *)malloc(16);
	if (!new) {
		return NULL;
	}
	new->next = NULL;
	new->data = data;
	return new;
}
