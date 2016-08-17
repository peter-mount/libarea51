#include <stdlib.h>
#include <area51/hashmap.h>
#include <area51/stream.h>

static void mapper(StreamData *d) {
    void *key = stream_getVal(d);
    if (key) {
        Hashmap *m = stream_getTaskContext(d);
        stream_setVal(d, hashmapGet(m, key), NULL);
    }
    stream_next(d);
}

int hashmapGetMapper(Stream *s, Hashmap *m) {
    return stream_invoke(s, mapper, m, NULL);
}
