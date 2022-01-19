#include "../inc/libmx.h"

void uls_printcols_c(ls_list **names, int rows, int num, int maxlen) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < num; j += rows) {
            mx_printstr_g(names[i + j]);
            if (names[i + j + 1] && (i + j + rows < num))
                mx_print_spaces_g(mx_strlen(names[i + j]->name), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}
