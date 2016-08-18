#include <stdlib.h>
#include <string.h>
#include <area51/hashmap.h>

/*
 * Mapping function to take a KeyValue and return its value
 */
void map_keyValue_value(StreamData *d) {
    KeyValue *k = stream_getVal(d);
    if (k)
        stream_setVal(d, k->value, NULL);
}
