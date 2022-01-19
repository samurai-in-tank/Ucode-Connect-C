#include "../inc/libmx.h"

char **uls_names_for_get(int argc, char **argv, int i, int *count) {
    int j = i;
    char **names = NULL;

    if (i == argc) {
        *count = 2;
        names = malloc(2 * sizeof(char *));
        names[0] = mx_strdup(".");
        names[1] = NULL;
    }
    else {
        j = argc;
        names = malloc((j - i + 1) * sizeof(char *));
        for(j = 0; argv[i]; i++, j++)
            names[j] = mx_strdup(argv[i]);
        names[j] = NULL;
        *count = j + 1;
    }
    return names;
}
