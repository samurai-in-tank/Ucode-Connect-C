#include "../inc/libmx.h"

char uls_check_chmode_1(char chmod) {
    if (chmod == '-')
        return chmod = 'S';
    else
        return chmod = 's';
}
