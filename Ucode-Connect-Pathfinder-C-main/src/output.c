#include "pathfinder.h"

static void printBase(t_names **prd) {
    char *string = mx_strdup("========================================");

    mx_printstr(string);
    mx_printchar('\n');
    mx_printstr((*prd)->name1);
    mx_printstr((*prd)->name2);
    mx_printstr((*prd)->name3);
    mx_printstr(string);
    mx_printchar('\n');
    mx_strdel(&(*prd)->name1);
    mx_strdel(&(*prd)->name2);
    mx_strdel(&(*prd)->name3);
    mx_strdel(&string);
    free(*prd);
    *prd = NULL;
}

static t_names *printHead(t_path *bond, char **set) {
    t_names *prd = malloc(1 * sizeof(t_names));
    int i = 0;

    prd->name1 = mx_strdup("Path: ");
    join(&(*prd).name1, set[bond->idPath]);
    prd->name2 = mx_strdup("Route: ");
    join(&(*prd).name2, set[bond->idPath]);
    prd->name3 = mx_strdup("Distance: ");
    for (; bond; bond = bond->nextConnect)
        i++;
    prd->num = i;
    return prd;
}

static void add_next_bond(t_names **prd, t_path *bond, char *distTo, char **set) {
    char *dist = mx_itoa(bond->distPath);
    
    join(&(*prd)->name2, " -> ");
    join(&(*prd)->name2, set[bond->idPath]);
    if (mx_strlen((*prd)->name3) != 10)
        join(&(*prd)->name3, " + ");
    join(&(*prd)->name3, dist);
    mx_strdel(&dist);
    if (bond->nextConnect == NULL) {
        join(&(*prd)->name1, " -> ");
        join(&(*prd)->name1, set[bond->idPath]);
        if ((*prd)->num != 2) {
            join(&(*prd)->name3, " = ");
            join(&(*prd)->name3, distTo);
        }
        join(&(*prd)->name2, "\n");
        join(&(*prd)->name1, "\n");
        join(&(*prd)->name3, "\n");
    }
}

static void display_path(t_path **disp, int distTo, char **set) {
    t_path *bond = *disp;
    t_names *prd = NULL;
    char *dist = mx_itoa(distTo);

    while (bond) {
        prd = printHead(bond, set);
        bond = bond->nextConnect;
        while (bond->nextConnect) {
            add_next_bond(&prd, bond, dist, set);
            bond = bond->nextConnect;
        }
        add_next_bond(&prd, bond, dist, set);
        printBase(&prd);
        bond = bond->nextPath;
    }
    mx_strdel(&dist);
}

void printOut(t_island **visited, int root, int size, char **set) {
    t_island *current = NULL;
    int sizeP;

    for (; root < size; root++) {
        current = *visited;
        while (current->islIndex != root)
            current = current->next;
        
        t_path *indexed = current->path;
        t_path *bonds = NULL;
        int i = 0;
        for (; indexed; indexed = indexed->nextPath) 
        {
            bonds = indexed;
            while (bonds) 
            {
                bonds->index = i;
                bonds = bonds->nextConnect;
            }
            i++;
        }
        sizeP = i;

        sortPath(&current->path, sizeP);
        display_path(&current->path, current->islDist, set);
    }
}
