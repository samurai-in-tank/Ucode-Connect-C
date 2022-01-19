#include "../inc/libmx.h"

char mx_check_per(ls_list *print) {
    if (LS_IS_DIR(print->info.st_mode))
        return 'd';
    if (LS_IS_LNK(print->info.st_mode))
        return 'l';
    if (LS_IS_BLK(print->info.st_mode))
        return 'b';
    if (LS_IS_CHR(print->info.st_mode))
        return 'c';
    if (LS_IS_FIFO(print->info.st_mode))
        return 'p';
    if (LS_IS_SOCK(print->info.st_mode))
        return 's';
    if (LS_IS_WHT(print->info.st_mode))
        return 'w';
    return '-';
}
