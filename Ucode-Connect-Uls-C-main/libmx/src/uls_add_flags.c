#include "../inc/libmx.h"

void uls_add_flags(st_fl **fl, char flag) {
    if (flag == 'T')
        (*fl)->T = 1;
    else if (flag == 'G' && isatty(1))
        (*fl)->G = 1;
    else if (flag == 'c') {
        (*fl)->u = 0;
        (*fl)->c = 1;
    }
    else if (flag == 't')
        (*fl)->t = 1;
    else if (flag == 'u') {
        (*fl)->u = 1;
        (*fl)->c = 0;
    }

    /* flags_sec */
    else if (flag == 'S')
        (*fl)->S = 1;
    else if (flag == 'r' && (*fl)->r != -1)
        (*fl)->r = 0;
    else if (flag == 'G' && !isatty(1))
        (*fl)->G = 0;
    else if (flag == 'R')
        (*fl)->R = 1;
    else if (flag == 'A')
        (*fl)->A = 1;
	else if (flag == 'g') {
        (*fl)->g = 1;
		(*fl)->l = 1;
	}
    else if (flag == 'o') {
        (*fl)->o = 1;
		(*fl)->l = 1;
	}
    else {
        /* flags_output */
        uls_nulloutput(fl);
        if (flag == 'l')
            (*fl)->l = 1;
        else if (flag == 'C')
            (*fl)->C = 1;
        else if (flag == '1')
            (*fl)->fr = 1;
        else if (flag == 'x')
            (*fl)->x = 1;
        else if (flag == 'm')
            (*fl)->m = 1;
        else
            uls_error_flag(fl, flag);
    }
}
