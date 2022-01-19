#include "uls.h"

void mx_output_x(ls_list **names) {
    int maxlen;
    struct winsize win;

    if (!names)
        return;
    maxlen = uls_max_len_names(names);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
        uls_print_names_x(names, maxlen, win.ws_col);
    else
        uls_print_names_x(names, maxlen, 80);
}
