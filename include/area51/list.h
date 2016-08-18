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
    typedef struct Node Node;
    struct Node {
        Node *n_succ;
        Node *n_pred;

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
        Node *n_succ;
        Node *n_pred;
    };

    typedef struct List {
        Node *l_head;
        Node *l_tail;
        Node *l_tailpred;
    } List;

    extern void list_init(List *list);
    extern void list_addHead(List *l, Node *n);
    extern void list_addTail(List *l, Node *n);
    extern Node *list_findNode(List *l, const char *name);
    extern Node *list_getHead(List *l);
    extern Node *list_getNext(Node *n);
    extern Node *list_getPred(Node *n);
    extern Node *list_getTail(List *l);
    extern void list_insert(List *l, Node *n, Node *after);
    extern int list_isEmpty(List *l);
    extern int list_isHead(Node *n);
    extern int list_isNode(Node *n);
    extern int list_isTail(Node *n);
    extern Node *list_remove(Node *n);
    extern Node *list_removeHead(List *l);
    extern Node *list_removeTail(List *l);
    extern int list_size(List *list);

    extern Node *node_alloc(char *name);
    extern void node_init(Node *node);
    extern void node_free(Node *n);

    // Sort a list using a comparator
    extern void list_sort(List *list, int (*comparator)(Node *a, Node *b));
    // Compare against a nodes name
    extern int list_name_compare(Node *a, Node *b);
    // Case insensitive compare against a nodes name
    extern int list_name_casecompare(Node *a, Node *b);

    extern void list_forEach(List *l, bool(*action)(Node *n, void *c), void *c);

    // Return a Stream of a list's content
    extern Stream *list_stream(List *);
    
    // Take the current value on a stream (Must be List) and flatMap it to the lists content
    extern int list_flatMap(Stream *s);

    // Map a Node to it's name/value
    extern int list_map_node_name(Stream *);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

