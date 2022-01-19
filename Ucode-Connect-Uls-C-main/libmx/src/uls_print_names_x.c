#include "../inc/libmx.h"

void uls_print_names_x(ls_list **names, int maxlen, int wincol) {
    int rows;
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;

    for(; names[num]; num++);
    if (maxlen * cols > wincol && cols != 1)
        cols--;
    if (num * maxlen > wincol) {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
            rows++;
        uls_print_cols_x(names, rows, cols, maxlen);
    }
    else
        for (int i = 0; names[i]; i++) {
            mx_printstr(names[i]->name);
            if (names[i + 1])
                mx_print_tab(mx_strlen(names[i]->name), maxlen);
        }
        mx_printchar('\n');
}
