#include "../inc/libmx.h"

int uls_print_sec(ls_list *args) {
    if (LS_IS_BLK(args->info.st_mode)) {
        uls_printstr("\033[34;46m");
        uls_print_name(args);
        return 1;
    }
    else if (LS_IS_CHR(args->info.st_mode)) {
        uls_printstr("\033[34;43m");
        uls_print_name(args);
        return 1;
    }
    else if (LS_IS_SOCK(args->info.st_mode)) {
        uls_printstr("\033[32m");
        uls_print_name(args);
        return 1;
    }
    return 0;
}
