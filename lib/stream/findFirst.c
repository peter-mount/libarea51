
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

static void findFirst(StreamData *d) {
    void (*action)(StreamData *) = d->task->taskContext;

    if (action)
        action(d);

    stream_terminate(d);
}

int stream_findFirst(Stream *s, void (*action)(StreamData *)) {
    return stream_invoke(s, findFirst, action, NULL);
}
