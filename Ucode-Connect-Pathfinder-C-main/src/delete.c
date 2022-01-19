#include "pathfinder.h"

static void popAll(t_path **head) {
    t_path *p = NULL;

    if (!head || !(*head)) 
        return;
    while ((*head)->nextConnect) {
        p = (*head)->nextConnect;
        free(*head);
        *head = p;
    }
    if (!(*head)->nextConnect && !(*head)->nextPath) {
        free(*head);
        *head = NULL;
        return;
    }

}

static void popNext(t_path **head) {
    t_path *p = NULL;

    if (!head || !(*head)) 
        return;
    if ((*head)->nextPath == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    else {
        p = (*head)->nextPath;
        free(*head);
        *head = p;
    }
}

void deletePath(t_path **head) {
    if (!head || !(*head)) 
        return;
    while(*head) {
        popAll(&(*head));
        popNext(&(*head));
    }
}

void deleteMatrix(int ***matrix, char **set) {
    int **mat = *matrix;
    int i = 0;

    while(set[i])
        i++;
    while(i >= 0) {
        free(*mat);
        mat++;
        i--;
    }
    free(*matrix);
    *matrix = NULL;
}
