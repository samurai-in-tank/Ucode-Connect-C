#include "pathfinder.h"

static void printErrLine(int nline) {
    nline++;
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(nline));
    mx_printerr(" is not valid\n");
    exit(0);
}

static void checkSpace(char **lines, char *file) {
    char *fl = file;
    char **ln = lines;
    int i = 0;
    int len = 0;

    if (*fl == '\n')
        printErrLine(0);
    while (*fl) {
        if (*fl == '\n' && *(fl + 1) == '\n')
            while (ln[i]) {
                len = mx_strlen(ln[i]);
                if (mx_strncmp(fl - len, ln[i], mx_strlen(ln[i])) == 0)
                    printErrLine(i + 1);
                i++;
            }
        fl++;
    }
}

static void checkline(char **lines, int nline) 
{
    int i = 0;
    int copy_i = 0;

    for (int n = 1; n <= nline; n++) {
        i = 0;
        copy_i = 0;

        while (mx_isalpha(lines[n][i])) 
            i++;
        if (i == 0 || lines[n][i] != '-')
            printErrLine(n);
        i++;

        copy_i = i;
        while (mx_isalpha(lines[n][copy_i])) 
            copy_i++;
        if (copy_i - i == 0 || lines[n][copy_i] != ',')
            printErrLine(n);
        copy_i++;
        i = copy_i;

        while (mx_isdigit(lines[n][copy_i])) copy_i++;
        if (copy_i - i == 0 || lines[n][copy_i] != '\0') printErrLine(n);
    }
}

static void parse(char *file) 
{
    char **lines = mx_strsplit(file, '\n');
    int nline = 0;
    int at = 0;
    
    while (lines[nline]) 
        nline++;
    if (lines[0][0] == '0') {
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
    while (lines[0][at]) 
    {
        if (!mx_isdigit(lines[0][at])) {
            mx_printerr("error: line 1 is not valid\n");
            exit(0);
        }
        at++;
    }
    checkline(lines, nline - 1);
    checkSpace(lines, file);
    mx_del_strarr(&lines);
}

void errorHandler(int argc, char *file, char **argv) 
{
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    if (!file) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
    }
    if (mx_strlen(file) == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(0);
    }
    parse(file);
}
