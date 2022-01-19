#include "../inc/libmx.h"

ls_list *uls_create_file_node(ls_list *arg) {
    ls_list *node = (ls_list *)malloc(1 * sizeof (ls_list));

    node->name = mx_strdup(arg->name);
    node->path = mx_strdup(arg->path);
    node->err = NULL;
    if (arg->err != NULL)
        node->err = mx_strdup(arg->err);
    lstat(node->path, &(node->info));
    if (arg->open != NULL)
        node->open = arg->open;
    else 
        node->open = NULL;
    return node;
}
