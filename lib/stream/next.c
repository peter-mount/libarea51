
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <area51/log.h>
#include "stream-int.h"

void stream_next(StreamData *d) {
    StreamTask *next = d->task->next;

    if (!next || !next->action)
        stream_terminate(d);
    else {
        d->task = next;

        if (d->task->stream->debug)
            stream_debug_task(d);

        d->task->action(d);
    }
}
