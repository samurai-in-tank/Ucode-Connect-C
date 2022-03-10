#include "libmx.h"

void mx_clear_list(t_list **list) {
    if (!list) {
        return;
    }
    t_list *a;
    while (*list) {
        a = (*list) -> next;
        (*list) -> next = NULL;
        free(*list);
        *list = a;
    }
}
