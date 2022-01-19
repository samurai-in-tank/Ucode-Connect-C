#include "uls.h"

void mx_output_m(ls_list **names, st_fl *fl) {
    struct winsize win;

    if (!names)
        return;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
        uls_print_names_m(names, win.ws_col, fl);
    else
        uls_print_names_m(names, 80, fl);
}
