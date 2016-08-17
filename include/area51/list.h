/* 
 * File:   list.h
 * Author: Peter T Mount
 *
 * Created on March 26, 2014, 1:16 PM
 */

#ifndef AREA51_LIST_H
#define AREA51_LIST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <area51/stream.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * A node within a list.
     */
    struct Node {
        struct Node *n_succ;
        struct Node *n_pred;

        /*
         * The name or value of the node
         */
        union {
            char *name;
            void *value;
        };
        int8_t pri;
        int8_t pad;
    };

    /**
     * A minimal Node. This can be used for all of the functions defined here
     * EXCEPT for node_free().
     */
    struct MinNode {
        struct Node *n_succ;
        struct Node *n_pred;
    };

    struct List {
        struct Node *l_head;
        struct Node *l_tail;
        struct Node *l_tailpred;
    };

    extern void list_init(struct List *list);
    extern void list_addHead(struct List *l, struct Node *n);
    extern void list_addTail(struct List *l, struct Node *n);
    extern struct Node *list_findNode(struct List *l, const char *name);
    extern struct Node *list_getHead(struct List *l);
    extern struct Node *list_getNext(struct Node *n);
    extern struct Node *list_getPred(struct Node *n);
    extern struct Node *list_getTail(struct List *l);
    extern void list_insert(struct List *l, struct Node *n, struct Node *after);
    extern int list_isEmpty(struct List *l);
    extern int list_isHead(struct Node *n);
    extern int list_isNode(struct Node *n);
    extern int list_isTail(struct Node *n);
    extern struct Node *list_remove(struct Node *n);
    extern struct Node *list_removeHead(struct List *l);
    extern struct Node *list_removeTail(struct List *l);
    extern int list_size(struct List *list);

    extern struct Node *node_alloc(char *name);
    extern void node_init(struct Node *node);
    extern void node_free(struct Node *n);

    // Sort a list using a comparator
    extern void list_sort(struct List *list, int (*comparator)(struct Node *a, struct Node *b));
    // Compare against a nodes name
    extern int list_name_compare(struct Node *a, struct Node *b);
    // Case insensitive compare against a nodes name
    extern int list_name_casecompare(struct Node *a, struct Node *b);

    extern void list_forEach(struct List *l, bool(*action)(struct Node *n, void *c), void *c);

    extern Stream *list_stream(struct List *);
    extern int list_map_node_name(Stream *);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

