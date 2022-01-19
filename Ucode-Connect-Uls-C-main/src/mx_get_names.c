#include "uls.h"

ls_list **mx_get_names(int argc, char **argv, int i) {
    int count = 0;
    char **name = uls_names_for_get(argc, argv, i, &count); //записывает в неймс название файла или папки
    ls_list **args = uls_create_list(name, count);

    mx_del_strarr(&name);
    return args;
}
