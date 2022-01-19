#include "../inc/libmx.h"

char *uls_get_minor(ls_list *print) {
    int minor_num = (int)(print->info.st_rdev & 0xffffff);
    char *minor = NULL;

    if (minor_num > 255)
        minor = uls_minor_to_hex(mx_nbr_to_hex(minor_num));
    else
        minor = mx_itoa(minor_num);

    return minor;
}
