#include "../inc/libmx.h"

void uls_print_link_and_color(ls_list *print, st_fl *fl) {
    if (fl->G == 1)
        mx_printstr_g(print);
    else if (LS_IS_LNK(print->info.st_mode)) {
        mx_printstr(print->name);
        mx_print_symblink(print);
    }
    else
        mx_printstr(print->name);
}
