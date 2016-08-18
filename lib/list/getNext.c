
#include <stdlib.h>
#include <area51/list.h>

Node *list_getNext(Node *n) {
    if (list_isNode(n) && list_isNode(n->n_succ))
        return n->n_succ;

    return NULL;
}
