#include "../inc/libmx.h"

void uls_create_FDE(ls_list ***dirs, ls_list ***args) {
    int nDir = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->err == NULL)
            if (LS_IS_DIR((*args)[i]->info.st_mode) && 
                mx_strcmp((*args)[i]->name, ".") != 0 &&
                mx_strcmp((*args)[i]->name, "..") != 0)
                nDir++;

    if (nDir > 0)
        *dirs = malloc((nDir + 1) * sizeof(ls_list *));
}
