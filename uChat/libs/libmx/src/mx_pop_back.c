#include "libmx.h"

void mx_pop_back(t_list **head) {
    if (head == NULL || *head == NULL) {
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        t_list *a = *head;
        while (a && a->next->next != NULL) {
            a = a->next;
        }
        free(a->next);
        a->next = NULL;
    }
}
