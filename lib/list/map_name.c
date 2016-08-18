
#include <stdio.h>
#include <stdlib.h>
#include <area51/list.h>
#include "area51/stream.h"

static void map_name(StreamData *d) {
    Node *n = stream_getVal(d);
    if(n)
        stream_setVal(d,n->name,NULL);
}

int list_map_node_name(Stream *s) {
    return stream_map(s, map_name);
}