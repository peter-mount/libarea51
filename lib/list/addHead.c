
#include <stdlib.h>
#include <area51/list.h>

void list_addHead(List *l, Node *n) {
    n->n_succ = l->l_head;
    n->n_pred = (Node *) & l->l_head;
    l->l_head->n_pred = n;
    l->l_head = n;
}
