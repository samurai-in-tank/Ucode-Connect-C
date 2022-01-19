#include "../inc/libmx.h"

void uls_out_put(ls_list **names, st_fl *fl) {
    for (int i = 0; names[i]; i++) {
        if (fl->G != 1)
            mx_printstr(names[i]->name);
        else
            mx_printstr_g(names[i]);
        mx_printchar('\n');
    }
}
