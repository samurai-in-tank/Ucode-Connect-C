#include "uls.h"

void mx_opendir(ls_list ***args, st_fl *fl) {
    ls_list **files = mx_get_files(&(*args), fl);

	if (files) {
		mx_out_put_menu(&files, fl, 0);
		if (*args)
			mx_printchar('\n');
		fl->fl = 1;
        mx_del_arr_arr(&files);
	}
    if (*args)
        uls_open_dir(&(*args), fl);
}
