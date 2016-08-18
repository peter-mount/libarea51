
#include <stdlib.h>
#include <area51/list.h>

/**
 * Initialise a List
 * @param list List to initialise
 */
void list_init(List *list) {
    list->l_head = (Node *) & list->l_tail;
    list->l_tail = NULL;
    list->l_tailpred = (Node *) & list->l_head;
}
