#include "pathfinder.h"

void islPopMiddle(t_island **unvisited, int index) {
    t_island *temp = NULL;
    t_island *leftOne = NULL;

    if (!unvisited || !(*unvisited)) 
        return;
    if ((*unvisited)->islIndex == index) {
        deletePath(&((*unvisited)->path));
        islPopFront(&(*unvisited));
    }
    else {
        temp = *unvisited;
        leftOne = temp;
        while (temp != NULL && temp->islIndex != index) {
            leftOne = temp;
            temp = temp->next;
        }
        if (temp && temp->islIndex == index) {
            if (temp->next)
                leftOne->next = temp->next;
            else
                leftOne->next = NULL;
            deletePath(&temp->path);
            free(temp);
            temp = NULL;
        }
    }
}

void islPopFront(t_island **head) {
    t_island *p = NULL;
    
    if (!head || !(*head)) 
        return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    else {
        p = (*head)->next;
        free(*head);
        *head = p;
    }
}

void join(char **res, char *s2) {
    char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
    int i = 0;
    int si = -1;
    char *s1 = *res;

    while(s1[++si]) {
        newstr[i] = s1[si];
        i++;
    }
    si = -1;
    while(s2[++si]) {
        newstr[i] = s2[si];
        i++;
    }
    mx_strdel(&(*res));
    *res = newstr;
}

void newPath(t_island **island, t_path **path, int isl, int dist) {
    t_island *new = (t_island *)malloc(1 * sizeof(t_island));
    new->islIndex = isl;
    new->islDist = dist;
    new->path = NULL;
    new->next = NULL;
    
    t_island *last = *island;

    if (path && *path)
        new->path = copyPath(&(*path));
    if (*island == NULL) {
        *island = new;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new;
    return;
}

t_island *distance(t_island **unvisited) {
    t_island *head = NULL;
    t_island *shortest = NULL;

    if (unvisited || *unvisited) {
        head = *unvisited;
        shortest = *unvisited;
        while (head) {
            if (head->islDist != 0) {
                if (shortest->islDist > head->islDist || !shortest->islDist)
                    shortest = head;
            }
            head = head->next;
        }
    }
    return shortest;
}
