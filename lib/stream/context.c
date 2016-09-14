
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

void *stream_context(StreamData *d) {
    return d && d->task && d->task->stream ? d->task->stream->context : NULL;
}

void *stream_getTaskContext(StreamData *d) {
    return d && d->task ? d->task->taskContext : NULL;
}

void stream_setTaskContext(StreamData *d, void *c, void (*fc)(void *)) {
    if (d && d->task) {
        if (d->task->taskContext && d->task->freeTaskContext)
            d->task->freeTaskContext(d->task->taskContext);
        d->task->taskContext = c;
        d->task->freeTaskContext = fc;
    }
}
