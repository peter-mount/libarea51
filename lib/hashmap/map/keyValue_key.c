#include <stdlib.h>
#include <area51/hashmap.h>

/*
 * Mapping function to take a KeyValue and return its key
 */
void map_keyValue_key(StreamData *d) {
    KeyValue *k = stream_getVal(d);
    if (k)
        stream_setVal(d, k->key, NULL);
}
