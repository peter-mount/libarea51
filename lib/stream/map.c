
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

static void map(StreamData *d) {
    void *(*mapper)(void *) = stream_getTaskContext(d);
    if (mapper)
        mapper(d);
    stream_next(d);
}

int stream_map(Stream *s, void (*mapper)(StreamData *)) {
    return stream_invoke(s, map, mapper, NULL);
}
