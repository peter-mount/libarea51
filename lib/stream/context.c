
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

void *stream_context(StreamData *d) {
    return d->task->stream->context;
}

void *stream_getTaskContext(StreamData *d) {
    return d->task->taskContext;
}

void stream_setTaskContext(StreamData *d, void *c, void (*free)(void *)) {
    if (d->task->taskContext && d->task->freeTaskContext)
        d->task->freeTaskContext(d->task->taskContext);
    d->task->taskContext = c;
    d->task->freeTaskContext = free;
}
