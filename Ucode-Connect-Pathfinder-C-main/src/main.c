#include "pathfinder.h"

static void parsing(char *fd, int ***matrix, char ***set) {
    char **arrarr = NULL;
    char **src = mx_strsplit(fd, '\n');

    createArray(src, &arrarr);
    createSet(&(*set), &arrarr, src[0]);
    *matrix = createMatrix(*set, &arrarr);
    mx_del_strarr(&src);
    mx_del_strarr(&arrarr);
}

int main(int argc, char *argv[]) 
{
    int **matrix = NULL;
    char **set = NULL;
    char *file = mx_file_to_str(argv[1]);

    errorHandler(argc, file, argv);
    parsing(file, &matrix, &set);
    pathFinder(matrix, set);
    deleteMatrix(&matrix, set);
    mx_strdel(&file);
    mx_del_strarr(&set);
    return 0;
}
