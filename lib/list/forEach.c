#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <area51/list.h>

/*
 * Run through each node of a list
 * 
 * @param l list to iterate
 * @param action Action to perform for each node
 * @param c optional context to pass to the action
 */
void list_forEach(struct List *l, bool(*action)(struct Node *n, void *c), void *c) {
    struct Node *n = list_getHead(l);
    while (list_isNode(n)) {
        if (!action(n, c))
            break;
        n = list_getNext(n);
    }
}
