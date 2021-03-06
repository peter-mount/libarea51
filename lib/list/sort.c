#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <area51/list.h>

/**
 * Comparator for a node's name
 */
int list_name_compare(Node *a, Node *b) {
    if (a->name == b->name)
        return 0;
    if (a->name == NULL)
        return -1;
    if (b->name == NULL)
        return 1;
    return strcmp(a->name, b->name);
}

/*
 * Case insensitive comparator for a node's name
 */
int list_name_casecompare(Node *a, Node *b) {
    if (a->name == b->name)
        return 0;
    if (a->name == NULL)
        return -1;
    if (b->name == NULL)
        return 1;
    return strcasecmp(a->name, b->name);
}

/**
 * Sort a list using a comparator
 * @param list
 * @param comparator
 */
void list_sort(List *list, int (*comparator)(Node *a, Node *b)) {
    if (list_isEmpty(list))
        return;

    Node *ptr1, *ptr2;
    bool swapped;
    do {
        swapped = false;
        ptr1 = list_getHead(list);
        while (list_isNode(ptr1) && list_isNode(ptr1->n_succ)) {
            ptr2 = ptr1->n_succ;
            if (comparator(ptr1, ptr2) > 0) {

                ptr2->n_pred = ptr1->n_pred;
                ptr1->n_succ = ptr2->n_succ;

                ptr1->n_pred = ptr2;
                ptr2->n_succ = ptr1;

                ptr2->n_pred->n_succ = ptr2;
                ptr1->n_succ->n_pred = ptr1;

                swapped = true;
            } else ptr1 = ptr2;
        }
    } while (swapped);
}
