#include "../inc/libmx.h"

void mx_print_spaces_g(int len, int maxlen) {
    int count = 0;

    count = maxlen - len;
    for (int i = 0; i < count; i++)
        mx_printchar(' ');
}
