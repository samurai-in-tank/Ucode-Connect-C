#include "../inc/libmx.h"

int uls_check_a(char *name, st_fl *fl) {
    if (fl->A != 1)
        return 0;
    if (mx_strcmp(name, ".") == 0)
        return 0;
    if (mx_strcmp(name, "..") == 0)
        return 0;
    return 1;
}
