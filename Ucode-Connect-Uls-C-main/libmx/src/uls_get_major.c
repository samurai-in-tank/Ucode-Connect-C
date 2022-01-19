#include "../inc/libmx.h"

char *uls_get_major(ls_list *print) {
    return mx_itoa((int)(((unsigned int)print->info.st_rdev >> 24) & 0xff));
}
