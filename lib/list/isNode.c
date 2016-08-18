
#include <stdlib.h>
#include <area51/list.h>

/**
 * Is node really a node?
 * 
 * This can happen if you are traversing the list. When you end up back on the list then this returns 0
 * 
 * @param n
 * @return 
 */
int list_isNode(Node *n) {
    return (n && n->n_succ && n->n_pred) ? 1 : 0;
}
