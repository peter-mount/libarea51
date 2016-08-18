#include <stdlib.h>
#include <string.h>
#include <area51/hashmap.h>

/*
 * Mapping function to take a KeyValue and return its value
 */
void *map_keyValue_value(void *v) {
    KeyValue *k = v;
    return k ? k->value : NULL;
}
