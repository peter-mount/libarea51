
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <area51/log.h>
#include "stream-int.h"

void stream_next(StreamData *d) {
    if (!d->task->stream->continueStream)
        return;

    bool debug = d->task->stream->debug;

    d->task = d->task->next;

    if (debug)
        logconsole("Moving forward to %lx val %lx", d->task, d->val);

    if (d->task && d->task->action)
        d->task->action(d);
    else
        d->task->stream->continueStream = false;
}
