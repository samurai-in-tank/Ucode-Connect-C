#include "pathfinder.h"

static int compare(t_path *bond, t_path *fast) {
    while (bond && fast) {
        if (bond->idPath > fast->idPath)
            return 1;
        if (bond->idPath < fast->idPath)
            return 0;
        bond = bond->nextConnect;
        fast = fast->nextConnect;
    }
    if (bond && !fast)
        return 1;
    return 0;
}

static void swap(t_path **disp, t_path **bond, t_path **fast) {
    t_path *temp = (*fast)->nextPath;
    t_path *cur = *disp;

    while(cur->nextPath != *fast)
        cur = cur->nextPath;
    addLink(&cur, &(*bond));
    cur = *disp;
    if (*disp == *bond)
        *disp = *fast;
    else {
        while (cur && cur->nextPath != *bond)
            cur = cur->nextPath;
        addLink(&cur, &(*fast));
    }
    addLink(&(*fast), &(*bond)->nextPath);
    addLink(&(*bond), &temp);
}

static void swp(t_path **disp, t_path **bond, t_path **fast) {
    t_path *temp = (*fast)->nextPath;
    t_path *cur = *disp;

    if ((*bond)->nextPath == *fast) {
            addLink(&(*fast), &(*bond));
            addLink(&(*bond), &temp);
        if (*disp == *bond)
            *disp = *fast;
        else {
            while (cur && cur->nextPath != *bond)
                cur = cur->nextPath;
            addLink(&cur, &(*fast));
        }
    }
    else 
        swap(&(*disp), &(*bond), &(*fast));
}

void sortPath(t_path **disp, int sizeP) {
    t_path *bond = *disp;
    t_path *fast = (*disp)->nextPath;

    for (int i = 0; i < sizeP; i++) {
        bond = *disp;
        fast = bond->nextPath;
        for (; bond->index != i; bond = bond->nextPath)
            fast = bond->nextPath;
        while (fast) {
            if (compare(bond, fast) == 1) {
                swp(&(*disp), &bond, &fast);
                for (bond = *disp; bond->index != i; bond = bond->nextPath)
                    fast = bond->nextPath;
            }
            else 
                fast = fast->nextPath;
        }
    }
}
