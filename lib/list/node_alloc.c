/**
 * Handle Node's in a List
 */

#include <stdlib.h>
#include <string.h>
#include <area51/list.h>

/**
 * Convenience method for simple lists.
 * 
 * Allocates a new Node.
 * 
 * Note: If this node is freed, then node_free() must be used. However name will
 * also be freed, so it should be allocated via malloc() or strdup().
 */
Node *node_alloc(char *name) {
    Node *node = (Node *) malloc(sizeof (Node));
    memset(node, 0, sizeof (Node));
    if (node) {
        node->n_pred = NULL;
        node->n_succ = NULL;
        node->name = name;
    }
    return node;
}

