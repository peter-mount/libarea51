/**
 * Handle Node's in a List
 */

#include <stdlib.h>
#include <area51/list.h>

void node_init(Node *node) {
    node->n_pred = NULL;
    node->n_succ = NULL;
    node->name = NULL;
}

