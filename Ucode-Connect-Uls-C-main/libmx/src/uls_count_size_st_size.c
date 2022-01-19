#include "../inc/libmx.h"

void uls_count_size_st_size(ls_size *size, ls_list *total) {
    char *name_grp = uls_check_group(total);
    char *name_pw = uls_check_pw(total);

    if (size->lnk < total->info.st_nlink)
        size->lnk = total->info.st_nlink;
    if (size->sz < total->info.st_size)
        size->sz = total->info.st_size;
    if (size->group < mx_strlen(name_grp))
        size->group = mx_strlen(name_grp);
    if (size->usr < mx_strlen(name_pw))
        size->usr = mx_strlen(name_pw);
    free(name_grp);
    free(name_pw);
}
