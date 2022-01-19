#include "../inc/libmx.h"

void uls_printcols_x(ls_list **names, int rows, int cols, int maxlen) {
    int j = 0;
    int tempcols = cols;

    for (int i = 0; i < rows; i++, cols += tempcols) {
        for (; names[j] && j < cols; j++) {
            mx_printstr_g(names[j]);
            if (names[j + 1] && (j != cols - 1))
                mx_print_spaces_g(mx_strlen(names[j]->name), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}
