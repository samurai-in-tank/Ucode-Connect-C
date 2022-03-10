// utils.c

#include "cheers.h"

char *itoa(int num) {
    char *str = NULL;
    asprintf(&str, "%d", num);
    return str;
}

char *get_str(char *str) {
    printf("Enter the %s : ", str);
    char *buff = malloc(1024);
    memset(buff, '\0', strlen(buff));
    while (buff[1] == '\0') {
        fgets(buff, 1024, stdin);
    }
    for (int i = 0; i < 1024; i++) {
        if (buff[i] == '\n')
            buff[i] = ' ';
    }
    printf("\n");
    return buff;
}

void read_l(app_t *app) {
    printf("\n");
    printf("0 - send, 1 - listen, 2 - login : ");
    scanf("%d", &app->type);
    printf("\n");
}
