#include "uls.h"

void mx_output_g(ls_list **names, st_fl *fl) {
    int maxlen;
    struct winsize win;

    if (!names)
        return;
    maxlen = mx_max_len_n_g(names);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    uls_printnames_g(names, maxlen, win.ws_col, fl);
}
