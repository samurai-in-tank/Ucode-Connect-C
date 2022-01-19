#include "../inc/libmx.h"

void uls_create_fde_apgread(ls_list ***files, ls_list ***dirs, ls_list ***errors, ls_list ***args) {
    int j = 0;
    int nDir = 0;
    int nErr = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->err == NULL) {
            if (!LS_IS_DIR((*args)[i]->info.st_mode) )
                j++;
            else
                nDir++;
        }
        else
            nErr++;
    if (j > 0)
        *files = malloc((j + 1) * sizeof(ls_list *));
    if (nDir > 0)
        *dirs = malloc((nDir + 1) * sizeof(ls_list *));
    if (nErr > 0)
        *errors = malloc((nErr + 1) * sizeof(ls_list *));
}
