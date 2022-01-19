#include "../inc/libmx.h"

void uls_error_flag(st_fl **fl, char flag) {
    free(*fl);
    fl = NULL;
    mx_printerr("uls: illegal option -- ");
    mx_printcharerr(flag);
    mx_printerr("\n");
    mx_printerr("usage: uls [-ACGRSTcfglmortux1] [file ...]\n");
    exit(-1);
}

void mx_printcharerr(char c) {
    write(2,&c,1);
}
