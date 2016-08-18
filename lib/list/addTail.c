
#include <stdlib.h>
#include <area51/list.h>

void list_addTail(List *l, Node *n) {
    n->n_succ = (Node *) & l->l_tail;
    n->n_pred = l->l_tailpred;
    l->l_tailpred->n_succ = n;
    l->l_tailpred = n;
}
