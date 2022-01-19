#include "uls.h"

void mx_long_out(ls_list **names, st_fl *fl, int flag) {
    ls_size *size = malloc(sizeof(ls_size));
    int blk_size = 0;
    int i = 0;

    uls_size_zero_st_size(size);
    for (i = 0; names[i]; i++) {
        blk_size += names[i]->info.st_blocks;
        uls_count_size_st_size(size, names[i]);
    }
    if (flag == 1) {
        mx_printstr("total ");
        mx_printint(blk_size);
        mx_printchar('\n');
    }
    uls_check_device(names, size);
    for (i = 0; names[i]; i++)
        mx_print_all(names[i], size, fl);
    free(size);
}
