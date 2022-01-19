#include "../inc/libmx.h"

ls_list **uls_create_list(char **name, int count) {
    ls_list **new = malloc(count * sizeof(ls_list *));
    int i = 0;

    for (i = 0; name[i]; i++)
        new[i] = uls_create_li_node(name[i]);
    new[i] = NULL;
    return new;
}
