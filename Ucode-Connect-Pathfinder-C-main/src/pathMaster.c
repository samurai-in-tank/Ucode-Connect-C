#include "pathfinder.h"

static t_path *addSingle(t_path **previous) {
    t_path *new = NULL;
    t_path *last = *previous;
    t_path *res = NULL;

    res = createPath(last->idPath, last->distPath);
    new = res;
    last = last->nextConnect;
    while (last) {
        new->nextConnect = createPath(last->idPath, last->distPath);
        last = last->nextConnect;
        new = new->nextConnect;
    }
    return res;
}

t_path *copyPath(t_path **data) {
    t_path *cur = NULL;
    t_path *res = NULL;
    t_path *new = NULL;
    t_path *fast = NULL;

    if (*data)
        cur = *data;
    res = addSingle(&cur);
    fast = res;
    cur = cur->nextPath;
    while (cur) {
        new = addSingle(&cur);
        addLink(&fast, &new);
        fast = fast->nextPath;
        cur = cur->nextPath;
    }
    return res;
}

t_path *createPath(int isl, int dist) {
	t_path *node = (t_path *)malloc(1 * sizeof(t_path));

	node->idPath = isl;
	node->distPath = dist;
	node->nextConnect = NULL;
	node->nextPath = NULL;
	return node;
}

void pathPushBack(t_path **path, t_path **previous, int isl, int dist) {
    t_path *last = *path;
    t_path *cur = *previous;
    t_path *new = NULL;
    
    while (last->nextPath != NULL)
        last = last->nextPath;
    while (cur) {
        new = addSinglePath(&cur, isl, dist);
        if (uniquePath(&new, &(*path)) == 1) {
            addLink(&last, &new);
            last = last->nextPath;
        }
        cur = cur->nextPath;
    }
}
