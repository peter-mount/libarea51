
#include <stdlib.h>
#include <area51/list.h>

/**
 * Removes a node from a List
 * @param n Node to remove
 * @return the node that was after this one before removal
 */
Node *list_remove(Node *n) {
    Node *next = n->n_succ;
    n->n_succ->n_pred = n->n_pred;
    n->n_pred->n_succ = n->n_succ;
    return next;
}
