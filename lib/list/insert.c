
#include <stdlib.h>
#include <area51/list.h>

void list_insert(List *l, Node *n, Node *after) {
    if (after == NULL) {
        list_addHead(l, n);
        return;
    }

    n->n_pred = after;
    n->n_succ = after->n_succ;
    after->n_succ = n;
    n->n_succ->n_pred = n;
}
