#include "uls.h"

void mx_printstr_g(ls_list *args) {
    if (uls_print_frst(args) == 1) {
    }
    else if (uls_print_sec(args) == 1) {
    }
    else if (LS_IS_FIFO(args->info.st_mode)) {
        uls_printstr("\033[33m");
        uls_print_name(args);
    }
    else if (LS_IS_WHT(args->info.st_mode)) {
        uls_printstr("\033[36m");
        uls_print_name(args);
    }
    else if (LS_IS_EXEC(args->info.st_mode)) {
        uls_printstr("\033[31m");
        uls_print_name(args);
    }
    else
        mx_printstr(args->name);
}
