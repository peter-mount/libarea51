
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

/*
 * Works by only running once if the task context is null. Once not null
 * this will just terminate the stream. We have to do it this way and not just
 * terminate once stream_next() is called to allow for running within a
 * substream (i.e. flatMap)
 */
static void findFirst(StreamData *d) {
    void *f = stream_getTaskContext(d);
    if (!f) {
        stream_next(d);
        stream_setTaskContext(d, (void *)findFirst, NULL);
    }
    stream_terminate(d);
}

int stream_findFirst(Stream *s) {
    return stream_invoke(s, findFirst, NULL, NULL);
}
