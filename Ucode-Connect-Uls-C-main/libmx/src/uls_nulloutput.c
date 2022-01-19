#include "../inc/libmx.h"

void uls_nulloutput(st_fl **fl) {
    (*fl)->x = 0;
    (*fl)->l = 0;
    (*fl)->C = 0;
    (*fl)->m = 0;
    (*fl)->fr = 0;
}
