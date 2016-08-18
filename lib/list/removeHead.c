
#include <stdlib.h>
#include <area51/list.h>

Node *list_removeHead(List *l) {
    Node *n = NULL;

    if (!list_isEmpty(l)) {
        n = l->l_head;
        n->n_succ->n_pred = n->n_pred;
        n->n_pred->n_succ = n->n_succ;
    }

    return n;
}
