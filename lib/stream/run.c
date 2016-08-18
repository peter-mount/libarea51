
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <area51/log.h>
#include "stream-int.h"

void *stream_run(Stream *s, void *context) {
    void *r = NULL;

    if (s) {
        bool debug = s->debug;

        if (debug)
            stream_debug_run("Running", s, context);

        s->context = context;
        s->result = NULL;
        while (s->continueStream) {
            StreamData *d = malloc(sizeof (StreamData));
            if (d) {
                memset(d, 0, sizeof (StreamData));
                d->task = s->start;

                if (debug)
                    stream_debug_task(d);

                if (d->task && d->task->action)
                    d->task->action(d);
                else
                    s->continueStream = false;

                if (d->val && d->free)
                    d->free(d->val);

                free(d);

            } else
                s->continueStream = false;

            if (debug)
                stream_debug_res("Continue", stream_long_void(s->continueStream));
        }

        if (debug)
            stream_debug_res("Stopped", s);

        r = stream_free(s);

        if (debug)
            stream_debug_res("Result", r);
    }

    return r;
}
