#include "uls.h"

int main(int argc, char *argv[]) {
    int count = 1;
    st_fl *fl = uls_get_flags(argv, &count); // добавили все флаги на файл и в структуру и если они есть  далее
    ls_list **args = mx_get_names(argc, argv, count);
    int ex = 0;

    if (args)
        mx_opendir(&args, fl);
    if (fl->ex == 1)
        ex = 1;
    free(fl);
    fl = NULL;

    return ex;
}
