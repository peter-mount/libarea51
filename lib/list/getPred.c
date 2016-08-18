
#include <stdlib.h>
#include <area51/list.h>

Node *list_getPred(Node *n) {
    if (list_isNode(n) && list_isNode(n->n_pred))
        return n->n_pred;

    return NULL;
}
