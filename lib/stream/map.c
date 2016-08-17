
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

static void map(StreamData *d) {
    void *(*mapper)(void *) = d->task->taskContext;
    if (mapper)
        d->val = mapper(d->val);
    stream_next(d);
}

int stream_map(Stream *s, void *(*mapper)(void *)) {
    return stream_invoke(s, map, mapper, NULL);
}
