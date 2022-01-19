#include "../inc/libmx.h"

void uls_print_cols(ls_list **names, int rows, int num, int maxlen) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < num; j += rows) {
            mx_printstr(names[i + j]->name);
            if (names[i + j + 1] && (i + j + rows < num))
                mx_print_tab(mx_strlen(names[i + j]->name), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}
