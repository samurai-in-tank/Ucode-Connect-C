#include "../inc/libmx.h"

char *uls_check_group(ls_list *total) {
    struct group *grp = NULL;
    char *name = NULL;
    
    grp = getgrgid(total->info.st_gid);
    if (grp) {
        name = mx_strdup(grp->gr_name);
        return name;
    }
    else {
        name = mx_itoa(total->info.st_gid);
        return name;
    }
}
