#include "../inc/libmx.h"

void uls_size_zero_st_size(ls_size *size) {
    size->lnk = 0;
    size->sz = 0;
    size->group = 0;
    size->usr = 0;
}
