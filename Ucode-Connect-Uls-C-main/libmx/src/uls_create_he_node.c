#include "../inc/libmx.h"

ls_list *uls_create_he_node(char *name, char *path) {
    ls_list *node = (ls_list *)malloc(1 * sizeof(ls_list));

    node->name = mx_strdup(name);
    node->path = mx_strdup(path);
    mx_join(&node->path, "/");
    mx_join(&node->path, name);
    node->err = NULL;

    if (lstat(node->path, &(node->info)) == -1)
        node->err = mx_strdup(strerror(errno));
    node->open = NULL;
    return node;
}
