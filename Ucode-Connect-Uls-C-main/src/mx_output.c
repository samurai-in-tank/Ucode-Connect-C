#include "uls.h"

void mx_out_put_all(ls_list ***args, st_fl *fl) {
    if (*args) {
        for (int i = 0; (*args)[i] != NULL; i++) {
            if (fl->fl == 1) {
                if ((*args)[i]->path[0] == '/' && (*args)[i]->path[1] == '/')
                    mx_printstr(&(*args)[i]->path[1]);
                else
                    mx_printstr((*args)[i]->path);
                mx_printchar(':');
				mx_printchar('\n');
            }
            uls_out_put_err_open(&(*args)[i], fl);
            if (fl->fl == 1 && (*args)[i+1])
                mx_printchar('\n');
        }
        mx_del_arr_arr(args);
    }
}
