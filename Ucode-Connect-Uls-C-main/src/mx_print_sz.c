#include "uls.h"

void mx_print_sz(ls_list *print, ls_size *size) {
    char *res_now = mx_itoa(print->info.st_size);
    char *res_sz = mx_itoa(size->sz);
    int counter = 0;

    if (mx_strlen(res_now) == mx_strlen(res_sz))
        uls_print_duo_cases(print, size);
    else if (mx_strlen(res_now) < mx_strlen(res_sz)) {
        counter = mx_strlen(res_now);
        while (counter != mx_strlen(res_sz)) {
            mx_printchar(' ');
            counter++;
        }
        uls_print_duo_cases(print, size);
    }
    mx_printchar(' ');
    free(res_now);
    free(res_sz);
}
