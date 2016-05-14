
#include <stdlib.h>
#include "area51/list.h"

struct Node *list_getPred(struct Node *n) {
    if (list_isNode(n) && list_isNode(n->n_pred))
        return n->n_pred;
    else
        return NULL;
}
