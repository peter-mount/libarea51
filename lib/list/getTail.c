
#include <stdlib.h>
#include <area51/list.h>

Node *list_getTail(List *l) {
    return l->l_head->n_succ == NULL ? NULL : l->l_tailpred;
}
