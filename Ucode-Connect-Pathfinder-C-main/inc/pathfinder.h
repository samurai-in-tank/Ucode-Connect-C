#pragma once

#include "libmx.h"

typedef struct  s_path {
    int idPath;
    int distPath;
    int index;
    struct s_path *nextConnect;
    struct s_path *nextPath;
}		        t_path;

typedef struct  s_island {
    int islIndex;
    int islDist;
    struct s_path *path;
    struct s_island *next;
}		        t_island;

typedef struct  s_pathlist{
    t_island *first;
    t_island *second;
    t_island *third;
    t_island *fourth;
}		        t_pathlist;

typedef struct  s_names {
    int num;
    char *name1;
    char *name2;
    char *name3;
}		        t_names;

typedef struct  s_islands {
    int isl1;
    int isl2;
    int mat;
}		        t_islands;

typedef struct  s_info {
    int size;
    int root;
}		        t_info;

t_path *createPath(int isl, int dist);
t_path *addPath(t_path **previous, int isl, int dist);
t_path *copyPath(t_path **data);
t_path *addSinglePath(t_path **previous, int isl, int dist);
void deletePath(t_path **head);
void newPath(t_island **island, t_path **path, int isl, int dist);
void sortPath(t_path **disp, int sizeP);
void pathPushBack(t_path **path, t_path **previous, int isl, int dist);
void pathFinder(int **matrix, char **set);
int uniquePath(t_path **new, t_path **pre);

int **createMatrix(char **set, char ***arrarr);
void deleteMatrix(int ***matrix, char **set);

void createArray(char **src, char ***arrarr);
void createSet(char ***set, char ***arrarr, char *numOfIsland);

void addLink(t_path **cur, t_path **new);

t_island *distance(t_island **unvisited);
void islPopFront(t_island **head);
void islPopMiddle(t_island **unvisited, int index);
void join(char **res, char *s2);

void errorHandler(int argc, char *file, char **argv);
void printOut(t_island **visited, int root, int size, char **set);
