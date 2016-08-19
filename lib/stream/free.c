
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

void *stream_free(Stream *s) {
    void *r = NULL;

    if (s) {

        StreamTask *t = s->start;
        while (t) {
            StreamTask *n = t->next;
            if (t->taskContext && t->freeTaskContext)
                t->freeTaskContext(t->taskContext);
            free(t);

            /*
             * Move to next task, abort if the freeNotFollow flag is set.
             * 
             * e.g. this is a flat mapped stream, so we don't want to free
             * the parent stream
             */
            t = t->freeNotFollow ? NULL : n;
        }

        if (s->context && s->freeContext)
            s->freeContext(s->context);

        r = s->result;

        free(s);
    }

    return r;
}
