#include <stdlib.h>
#include <area51/list.h>
#include <area51/stream.h>

static Stream *flatMap(StreamData *d, void *c) {
    return list_stream((List *) stream_getVal(d));
}

int list_flatMap(Stream *s) {
    return stream_flatMap(s, flatMap, NULL);
}
