#include "../inc/libmx.h"

char uls_check_chmode_2(char *chmod) {
    if (chmod[9] == '-')
        return chmod[9] = 'T';
    else
        return chmod[9] = 't';
}
