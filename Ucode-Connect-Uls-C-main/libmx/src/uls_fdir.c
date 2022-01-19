#include "../inc/libmx.h"

void uls_fdir(ls_list **args, ls_types *num, ls_list ***files, ls_list ***dirs) {
    if (!LS_IS_DIR((*args)->info.st_mode)) {
        (*files)[num->n_f++] = uls_create_file_node_for_get_file((*args));
        (*files)[num->n_f] = NULL;
    }
    else {
        (*dirs)[num->n_d++] = uls_create_file_node_for_get_file((*args));
        (*dirs)[num->n_d] = NULL;
    }
}
