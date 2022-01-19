#include "../inc/libmx.h"

int uls_count_read(ls_list **arg, st_fl *fl) {
    int count = 0;
    ls_list *args = *arg;
    DIR *dptr;
    struct dirent *ds;

    if (LS_IS_DIR(args->info.st_mode) ||  LS_IS_LNK(args->info.st_mode)) {
        if ((dptr = opendir(args->path)) != NULL) {
            while ((ds = readdir(dptr)) != NULL)
                if (ds->d_name[0] != '.' 
                    || uls_check_a(ds->d_name, fl) == 1)
                    count++;
            closedir(dptr);
        }
        else {
            (*arg)->err = mx_strdup(strerror(errno));
            fl->ex = 1;
            return -1;
        }
    }
    return count;
}
