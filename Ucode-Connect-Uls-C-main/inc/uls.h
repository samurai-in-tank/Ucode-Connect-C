#include "string.h"
#include "libmx.h"

void mx_output_del_files(ls_list ***args, st_fl *fl);
void mx_edit_time(ls_list *print, char *t, st_fl *fl);
void mx_long_out(ls_list **names, st_fl *fl, int flag);
ls_list **mx_get_files(ls_list ***args, st_fl *fl);
ls_list **mx_get_names(int argc, char **argv, int i);
void mx_opendir(ls_list ***args, st_fl *fl);
void mx_output_c(ls_list **names);
void mx_output_g(ls_list **names, st_fl *fl);
void mx_output_m(ls_list **names, st_fl *fl);
void mx_output_x(ls_list **names);
void mx_out_put_all(ls_list ***args, st_fl *fl);
void mx_print_all(ls_list *print, ls_size *size, st_fl *fl);
void mx_print_per(ls_list *print);
void mx_print_symblink(ls_list *print);
void mx_print_sz(ls_list *print, ls_size *size);
void mx_out_err(ls_list ***error, st_fl *fl);
void mx_printstr_g(ls_list *args);
void mx_sort(ls_list ***disp, st_fl *fl);


