#include "../inc/libmx.h"

int uls_print_frst(ls_list *args) {
    if (LS_IS_DIR(args->info.st_mode)) {
        uls_printstr("\033[34m");
        uls_print_name(args);
        return 1;
    }
    else if (LS_IS_LNK(args->info.st_mode)) {
        uls_printstr("\033[35m");
        uls_print_name(args);
        return 1;
    }
    else if (args->info.st_mode & S_IXOTH) {
        uls_printstr(COLOR_RED);
        uls_print_name(args);
        return 1;
    }

    return 0;
}
