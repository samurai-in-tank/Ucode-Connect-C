#include "libmx.h"

int mx_list_size(t_list *list) {
	if (!list) {
		return 0;
	}
	int ind = 0;
	while (list) {
		list = list->next;
		ind++;
	}
	return ind;
}
