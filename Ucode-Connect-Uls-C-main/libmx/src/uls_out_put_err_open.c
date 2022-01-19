#include "../inc/libmx.h"

void uls_out_put_err_open(ls_list **args, st_fl *fl) {
    if ((*args)->open != NULL) {
        mx_out_put_menu(&(*args)->open, fl, 1);
        if (fl->R == 1) {
            fl->fl = 1;
            mx_output_del_files(&(*args)->open, fl);
            if ((*args)->open) {
                mx_printchar('\n');
                mx_opendir(&(*args)->open, fl);
            }
        }
    }
    else if ((*args)->err != NULL) {
        mx_printerr("uls: ");
        mx_printerr((*args)->path);
        mx_printerr(": ");
        mx_printerr((*args)->err);
        mx_printerr("\n");
    }
}
