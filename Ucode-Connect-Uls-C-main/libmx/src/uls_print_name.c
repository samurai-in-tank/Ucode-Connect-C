#include "../inc/libmx.h"

void uls_print_name(ls_list *args) {
    mx_printstr(args->name);
    uls_printstr(COL_RESETs);
}
