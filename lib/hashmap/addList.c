#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <area51/hashmap.h>
#include <area51/list.h>
#include <area51/string.h>

/**
 * Add's a value to a key. Unlike hashmapPut the underlying value is a
 * struct List, which is what will be returned by hashmapGet.
 * 
 * If the key does not exist then this will create a new list which will be
 * added to the map.
 * 
 * In either case the value will then be added to the list.
 * Also, the value will be attached to the List's Node's name field.
 * 
 * @param m Hashmap
 * @param k key
 * @param v value to add
 * @returns The underlying list
 */
List*hashmapAddList(Hashmap *m, void *k, void *v) {
    List*l = (List*) hashmapGet(m, k);
    if (!l) {
        l = (List*) malloc(sizeof (struct List));
        list_init(l);
        hashmapPut(m, k, l);
    }

    Node *n = node_alloc((char *) v);
    list_addTail(l, n);
    return l;
}
