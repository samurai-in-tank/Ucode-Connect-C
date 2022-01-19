#include "../inc/libmx.h"

ls_types *uls_create_num() {
    ls_types *num = malloc(sizeof (ls_types));

    num->n_d = 0;
    num->n_e = 0;
    num->n_f = 0;
    num->i = 0;
    return num;
}
