#include "../inc/libmx.h"

void uls_print_duo_cases(ls_list *print, ls_size *size) {
    char *major = uls_get_major(print);
    char *minor = uls_get_minor(print);

    if (size->is_dev == true)
        if (LS_IS_BLK(print->info.st_mode) ||  LS_IS_CHR(print->info.st_mode)) {
            uls_print_spaces(2 - mx_strlen(major));
            mx_printstr(major);
            mx_printchar(',');
            mx_printchar(' ');
            uls_print_spaces(2 - mx_strlen(minor));
            mx_printstr(minor); 
        }
        else {
            mx_printstr("       ");
            mx_printint(print->info.st_size);
        }
    else
       mx_printint(print->info.st_size); 
    free(major);
    free(minor);
}
