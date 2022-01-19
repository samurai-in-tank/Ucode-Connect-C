#include "../inc/libmx.h"

void uls_open_dir(ls_list ***args, st_fl *fl) {
    DIR *dptr;
    struct dirent *ds;
    int count = 0;

    for (int i = 0; (*args)[i] != NULL; i++) {
        count = uls_count_read(&(*args)[i], fl);
        if (count > 0) {
            (*args)[i]->open = malloc((count + 1) * sizeof(ls_list *));
            if ((dptr = opendir((*args)[i]->path)) != NULL) {
                for (count = 0; (ds = readdir(dptr)) != NULL;)
                    if (ds->d_name[0] != '.' 
                        || uls_check_a(ds->d_name, fl) == 1)
                        (*args)[i]->open[count++] = 
                        uls_create_he_node(ds->d_name, (*args)[i]->path);
                (*args)[i]->open[count] = NULL;
            closedir(dptr);
            }
        }
    }
    mx_out_put_all(args, fl);
}
