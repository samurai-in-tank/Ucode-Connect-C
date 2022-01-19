#include "../inc/libmx.h"

int uls_cmp_sort(ls_list *first, ls_list *second, st_fl *fl) {
    if (fl->S == 1) {
        if (first->info.st_size < second->info.st_size)
            return 1;
        if (first->info.st_size == second->info.st_size)
            return mx_strcmp(first->name, second->name);
    }
    else if (fl->t == 1 && fl->c != 1 && fl->u != 1) {
        if (first->info.st_mtime == second->info.st_mtime) {
            if (first->info.st_mtimespec.tv_nsec == second->info.st_mtimespec.tv_nsec)
                return mx_strcmp(first->name, second->name);
            return (first->info.st_mtimespec.tv_nsec < second->info.st_mtimespec.tv_nsec) ? 1 : 0;
        }
        return (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
    }
    return uls_cmp_sort_1(first, second, fl);
}
