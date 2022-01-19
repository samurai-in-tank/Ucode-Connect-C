#include "../inc/libmx.h"

void mx_get_user_name(ls_list *print, int usr) {
    struct passwd *pw = getpwuid(print->info.st_uid);
    int counter = 0;
    char *name = NULL;

    if (pw)
        name = mx_strdup(pw->pw_name);
    else
        name = mx_itoa(print->info.st_uid);
    if (mx_strlen(name) == usr)
       mx_printstr(name);
    else if (mx_strlen(name) < usr) {
        counter = mx_strlen(name);
        mx_printstr(name);
        while (counter != usr) {
            mx_printchar(' ');
            counter++;
        }
    }
    mx_printstr("  ");
    free(name);
}
