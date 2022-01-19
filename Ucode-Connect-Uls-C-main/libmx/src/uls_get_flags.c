#include "../inc/libmx.h"

st_fl *uls_get_flags(char *argv[], int *i) {
    st_fl *fl = malloc(sizeof(st_fl));

    fl->r = 1;
    while(argv[(*i)]) {
        //error if --- and more
        if (argv[(*i)][0] == '-') {
            if (argv[(*i)][1] == '-') {    
                if (argv[(*i)][2] == '-') {    
                    mx_printerr("usage: uls [-ACGRSTcfglmortux1] [file ...]\n");
                    exit(-1);
                    break;
                } else
                (*i)++;
                break;
            }
            //если конец строки и нету больше флагов выход
            if (argv[(*i)][1] == '\0')
                break;
            for (int j = 1; argv[(*i)][j]; j++) {
                uls_add_flags(&fl, argv[(*i)][j]);//считывает каждый элемент до тех пор пока не считает все флаги указаные  и добавляет их к выполненеию програмы
            }
        }
        else
            break;
        (*i)++;
    }
    return fl;
}
