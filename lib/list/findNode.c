#include <stdlib.h>
#include <string.h>
#include "area51/config.h"
#include <area51/list.h>

/**
 * Finds the NamedNode in a list by name.
 * 
 * @param l List
 * @param name Name to find
 * @return NamedNode or NULL if not found
 */
Node *list_findNode(List *l, const char *name) {

    Node *n = list_getHead(l);
    while (list_isNode(n)) {
        if (strcmp(n->name, name) == 0)
            return n;
        n = n->n_succ;
    }

    return NULL;
}
