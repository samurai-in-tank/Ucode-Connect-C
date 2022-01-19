#include "pathfinder.h"

void addLink(t_path **cur, t_path **new) 
{
    t_path *current = *cur;
    while (current->nextConnect) 
    {
        current->nextPath = *new;
        current = current->nextConnect;
    }
    current->nextPath = *new;
}

t_path *addSinglePath(t_path **previous, int isl, int dist) 
{
    t_path *new = NULL;
    t_path *last = *previous;
    t_path *res = NULL;

    if (!last) return res = createPath(isl, dist);

    res = createPath(last->idPath, last->distPath);
    new = res;
    last = last->nextConnect;
    while (last) 
    {
        new->nextConnect = createPath(last->idPath, last->distPath);
        last = last->nextConnect;
        new = new->nextConnect;
    }
    new->nextConnect = createPath(isl, dist);

    return res;
}

t_path *addPath(t_path **previous, int isl, int dist) 
{
    t_path *cur = NULL;
    t_path *res = NULL;
    t_path *new = NULL;
    t_path *fast = NULL;

    if (*previous)
        cur = *previous;
    res = addSinglePath(&cur, isl, dist);
    fast = res;
    if (cur)
        cur = cur->nextPath;
    while (cur) {
        new = addSinglePath(&cur, isl, dist);
        addLink(&fast, &new);
        fast = fast->nextPath;
        cur = cur->nextPath;
    }
    return res;
}
