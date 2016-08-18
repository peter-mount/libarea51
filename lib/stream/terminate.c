
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stream-int.h"

void stream_terminate(StreamData *d) {
    if (d && d->task && d->task->stream)
        d->task->stream->continueStream = false;
}
