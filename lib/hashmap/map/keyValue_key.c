#include <stdlib.h>
#include <area51/hashmap.h>

/*
 * Mapping function to take a KeyValue and return its key
 */
void *map_keyValue_key(void *v) {
    KeyValue *k = v;
    return k ? k->key : NULL;
}
