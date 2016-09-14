#include <stdlib.h>
#include <area51/stream.h>
#include <string.h>
#include <area51/log.h>
#include "../../libarea51/lib/stream/stream-int.h"

static void setVal(StreamData *d) {
    d->val = stream_getTaskContext(d);
    d->free = NULL;
    stream_next(d);

    // We are a singleton so don't repeat
    stream_terminate(d);
}

Stream *stream_of(void *v, void (*f)(void *)) {
    Stream *s = stream_new();
    if (s) {
        if (stream_invoke(s, setVal, v, f)) {
            stream_free(s);
            if (f&&v)
                f(v);
            return NULL;
        }
    }
    return s;
}
