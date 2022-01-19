#include "../inc/libmx.h"

bool uls_check_device(ls_list **names, ls_size *size) {
    for (int i = 0; names[i]; i++)
        if (LS_IS_BLK(names[i]->info.st_mode) || LS_IS_CHR(names[i]->info.st_mode))
            return size->is_dev = true;
    return size->is_dev = false;
}
