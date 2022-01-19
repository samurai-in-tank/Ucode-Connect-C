#include "uls.h"

ls_list **mx_get_files(ls_list ***args, st_fl *fl) {
    ls_list **files = NULL;
    ls_list **dirs = NULL;
    ls_list **errors = NULL;
    ls_types *num = uls_create_num();

    uls_create_fde_apgread(&files, &dirs, &errors, args);
    while ((*args)[num->i] != NULL) {
        if ((*args)[num->i]->err == NULL)
            uls_fdir(&(*args)[num->i], num, &files, &dirs);
        else {
            errors[num->n_e++] = uls_create_file_node_for_get_file((*args)[num->i]);
            errors[num->n_e] = NULL;
        }
        num->i++;
    }

    if (num->n_d > 1)
        fl->fl = 1;
    uls_del_li_array(args, dirs);
    mx_out_err(&errors, fl);
    free(num);
    return files;
}
