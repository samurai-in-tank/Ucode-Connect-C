#include "../inc/libmx.h"

char *uls_check_pw(ls_list *total) {
    struct passwd *pw = NULL;
    char *name = NULL;

    pw = getpwuid(total->info.st_uid);
    if (pw) {
        name = mx_strdup(pw->pw_name);
        return name;
    }
    else {
        name = mx_itoa(total->info.st_uid);
        return name;    
    }
}
