
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <area51/log.h>
#include "stream-int.h"

void *stream_run(Stream *s, void *context) {
    bool debug = s->debug;

    if (debug)
        logconsole("Running stream %lx context %lx", s, context);

    if (s) {
        s->context = context;
        s->result = NULL;
        while (s->continueStream) {
            StreamData *d = malloc(sizeof (StreamData));
            if (d) {
                memset(d, 0, sizeof (StreamData));
                d->task = s->start;

                if (debug)
                    logconsole("Invoking %16lx val %lx", d->task ? d->task->action : NULL, d->val);

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
                logconsole("continueStream %s", s->continueStream ? "YES" : "NO");
        }
    }

    if (debug)
        logconsole("Stream finished");

    void *r = stream_free(s);

    if (debug)
        logconsole("Stream result %lx", r);

    return r;
}
