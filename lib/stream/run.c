
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <area51/log.h>
#include "stream-int.h"

/*
 * Run a stream
 * @param s Stream
 * @param context optional context object
 */
void *stream_run(Stream *s, void *context) {
    return stream_run_r(s, s, context);
}

/*
 * Run a stream
 * @param ps parent Stream
 * @param s child Stream
 * @param context optional context object
 */
void *stream_run_r(Stream *ps, Stream *s, void *context) {
    void *r = NULL;

    if (s) {
        unsigned int debug = s->debug;

        if (debug == 1)
            stream_debug_run(s, "Run", s, context);

        s->context = context;
        s->result = NULL;
        while (s->continueStream && ps->continueStream) {
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
        }

        if (debug == 1)
            stream_debug_res(s, "Sto", s);

        r = stream_free(s);

        if (debug == 1)
            stream_debug_res(s, "Res", r);
    }

    return r;
}
