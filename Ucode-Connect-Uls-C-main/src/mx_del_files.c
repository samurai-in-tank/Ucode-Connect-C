#include "uls.h"

void mx_output_del_files(ls_list ***args, st_fl *fl) {
   ls_list **dirs = NULL;
    int nDir = 0;

    uls_create_FDE(&dirs, args);
    for (int i = 0; (*args)[i] != NULL; i++) {
        if ((*args)[i]->err == NULL) {
            if (LS_IS_DIR((*args)[i]->info.st_mode) && 
                mx_strcmp((*args)[i]->name, ".") != 0 && 
                mx_strcmp((*args)[i]->name, "..") != 0) {
                dirs[nDir++] = uls_create_file_node((*args)[i]);
                dirs[nDir] = NULL;
            }
        }
    }
    fl->fl = 1;
    uls_del_li_array(args, dirs);
}
