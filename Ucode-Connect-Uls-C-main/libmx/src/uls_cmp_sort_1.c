#include "../inc/libmx.h"

int uls_cmp_sort_1(ls_list *first, ls_list *second, st_fl *fl) {
    if (fl->u == 1 && fl->t == 1 && fl->S != 1) {
        if (first->info.st_atime == second->info.st_atime) {
            if (first->info.st_atimespec.tv_nsec == second->info.st_atimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_atimespec.tv_nsec < second->info.st_atimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_atime < second->info.st_atime) ? 1 : 0;
    }
    else 
        return uls_cmp_sort_2(first, second, fl);
}
