
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

int stream_invoke(Stream *s, void(*action)(StreamData *), void *context, void (*freeContext)(void *)) {
    if (s ) {
        StreamTask *t = malloc(sizeof (StreamTask));
        if (t) {
            memset(t, 0, sizeof (StreamTask));
            t->action = action;
            t->stream = s;
            t->taskContext = context;
            t->freeTaskContext = freeContext;

            if (s->start) {
                s->tail->next = t;
                s->tail = t;
            } else {
                s->start = s->tail = t;
            }
            return EXIT_SUCCESS;
        }

    }

    return EXIT_FAILURE;
}
