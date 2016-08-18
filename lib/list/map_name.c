
#include <stdio.h>
#include <stdlib.h>
#include <area51/list.h>
#include "area51/stream.h"

static void *map_name(void *v) {
    return v ? ((Node *) v)->name : NULL;
}

int list_map_node_name(Stream *s) {
    return stream_map(s, map_name);
}