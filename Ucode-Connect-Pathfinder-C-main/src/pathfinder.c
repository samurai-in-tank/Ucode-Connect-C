#include "pathfinder.h"

static void state1(t_island **un, t_island **cur, t_island **v, t_info *in) {
    *un = NULL;
    *v = NULL;
    for (int i = 0; i < in->size; i++)
        newPath(&(*un), NULL, i, 0);
    *cur = *un;
    while ((*cur)->islIndex != in->root)
        *cur = (*cur)->next;
    (*cur)->path = createPath(in->root, 0);
    newPath(&(*v), &(*cur)->path, (*cur)->islIndex, (*cur)->islDist);
    islPopMiddle(&(*un), in->root);
    *cur = *v;
}

static void state2(t_island **un, t_island **cur, int **mat, t_islands **m) {
    t_island *h = *un;
    int sum = 0;
    while (h != NULL) {
        (*m)->isl1 = (*cur)->islIndex;
        (*m)->isl2 = h->islIndex;
        (*m)->mat = mat[(*m)->isl1][(*m)->isl2];
        if ((*m)->mat != 0 && h->islDist == 0) {
            h->islDist = (*cur)->islDist + (*m)->mat;

            sum += h->islDist;
            if (sum < 0) { 
                mx_printerr("error: sum of bridges lengths is too big\n");
                exit(0);
            } 

            h->path = addPath(&(*cur)->path, (*m)->isl2, (*m)->mat);
        } else if ((*m)->mat != 0) {
            if ((*cur)->islDist + (*m)->mat == h->islDist)
            pathPushBack(&h->path, &(*cur)->path, (*m)->isl2, (*m)->mat);
            if ((*cur)->islDist + (*m)->mat < h->islDist) {
                h->islDist = (*cur)->islDist + (*m)->mat;
                deletePath(&h->path);
                h->path = addPath(&(*cur)->path, (*m)->isl2, (*m)->mat);
            }
        }
        h = h->next;
    }
}

static void state3(t_pathlist **l, int **matrix, char **set) {
    (*l)->fourth = distance(&(*l)->first);
    newPath(&(*l)->second, &(*l)->fourth->path, (*l)->fourth->islIndex, (*l)->fourth->islDist);
    islPopMiddle(&(*l)->first, (*l)->fourth->islIndex);
    (*l)->third = (*l)->third->next;
    if ((*l)->third->path == NULL) {
        deleteMatrix(&matrix, set);
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
}

static void algorithm(int **matrix, char **set, t_info *in) {
    t_pathlist *l = malloc(sizeof(t_pathlist));
    l->first = NULL;
    l->second = NULL;
    l->third = NULL;
    l->fourth = NULL;

    t_islands *m = NULL;

    state1(&l->first, &l->third, &l->second, in);
    while (l->first && l->first != NULL) {
        m = malloc(sizeof(t_islands));
        state2(&l->first, &l->third, matrix, &m);
        free(m);
        m = NULL;
        state3(&l, matrix, set);
    }
    printOut(&l->second, in->root+1, in->size, set);
    while (l->second != NULL) {
        deletePath(&l->second->path);
        islPopFront(&l->second);
    }
    free(l);
    l = NULL;
}

void pathFinder(int **matrix, char **set) {
    int size = 0;
    int i = 0;
    t_info *in = malloc(sizeof(t_info));

    while (set[size]) 
        size++;
    in->size = size;
    while (i < size - 1) {
        in->root = i;
        algorithm(matrix, set, in);
        i++;
    }
    free(in);
    in = NULL;
}
