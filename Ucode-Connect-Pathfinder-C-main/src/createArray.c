#include "pathfinder.h"

static void countLines(char *line, char **island1, char **island2, char **dis) {
    int i = 0;
    char *str = line;
    
    while(str[i] != '-') {
        i++;
    }
    *island1 = mx_strndup(str, i);
    str += i + 1;
    i = 0;
    while(str[i] != ',') {
        i++;
    }
    *island2 = mx_strndup(str, i);
    str += i + 1;
    i = 0;
    while(str[i] != '\0') {
        i++;
    }
    *dis = mx_strndup(str, i);
}

static void fill(char ***arrarr, char **lines, int line) {
    char **arr = *arrarr;
    char *island1 = NULL;
    char *island2 = NULL;
    char *dist = NULL;
    int nline = line;

    int arr_indicator = 0;
    while(lines[line]) {
        countLines(lines[line], &island1, &island2, &dist);
        if (mx_strcmp(island1,island2) == 0 && mx_atoi(dist) != 0) {
            nline++;
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(nline));
            mx_printerr(" is not valid\n");
            exit(0);
        }

        arr[arr_indicator++] = mx_strdup(island1);
        mx_strdel(&island1);

        arr[arr_indicator++] = mx_strdup(island2);
        mx_strdel(&island2);

        arr[arr_indicator++] = mx_strdup(dist);
        mx_strdel(&dist);

        for (int i = 0; i < arr_indicator - 3; i += 3) {
            if (mx_strcmp(arr[arr_indicator - 3], arr[i]) == 0 && mx_strcmp(arr[arr_indicator - 2], arr[i + 1]) == 0) 
            {
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
            if (mx_strcmp(arr[arr_indicator - 2], arr[i]) == 0 && mx_strcmp(arr[arr_indicator - 3], arr[i + 1]) == 0)
            {
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
        }
        
        line++;
    }
}

void createArray(char **lines, char ***arrarr) {
    int line = 1;

    while (lines[line]) {
        line++;
    }
    *arrarr = (char **)malloc((line * 3 + 1) * sizeof(char *));
    fill(&(*arrarr), lines, 1);
}
