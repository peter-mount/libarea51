#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <area51/log.h>
#include "stream-int.h"

static const char *SEP = "-----------------------------------------------------------";
static const char *RES = " %03d     %3s %12lx";
static const char *RUN = " %03d     %3s %12lx %16lx";
//static const char *NUM = "%8s %16lx %16lx %16lx";
static const char *STR = "%8s %16s %16s %16s";
static const char *STP = " %03d-%03d %16lx %16lx %16lx %s";
static const char *ACTION = "Action";
static const char *CONTEXT = "Context";
static const char *NEXT = "Next";
static const char *STEP = "Step";
static const char *TASK = "Task";
static const char *VALUE = "Value";
static const char *STREAM = "Stream";
static const char *BLANK = "";
static int sid = 0;

void stream_debug_task(StreamData *d) {
    logconsole(STP, d->task->stream->sid, d->task->tid, d->task, stream_getVal(d), stream_getTaskContext(d), d->task->sname);
}

void stream_debug_res(Stream *st, const char *s, void *r) {
    logconsole(RES, st->sid, s, r);
}

void stream_debug_run(Stream *st, const char *s, void *a, void *b) {
    logconsole(RUN, st->sid, s, a, b);
}

void stream_debug_r(Stream *s, bool child) {

#ifdef DEBUG_FULL
    logconsole(SEP);
    stream_debug_res(STREAM, s);
#endif

    if (s) {
        s->sid = ++sid;
        s->debug = child ? 2 : s->debug > 1 ? s->debug : 1;
        StreamTask *t = s->start;
        int c = 0;

#ifdef DEBUG_FULL
        logconsole(STR, STEP, TASK, NEXT, CONTEXT);
        logconsole(SEP);
#endif

        while (t) {
            t->tid = ++c;

            if (!t->sname)
                t->sname = BLANK;

#ifdef DEBUG_FULL
            logconsole(STP, sid, t->tid, t, t->next, t->taskContext, t->sname);
#endif

            t = t->next;
        }

#ifdef DEBUG_FULL
        if (!child) {
            logconsole(SEP);
            logconsole(STR, ACTION, TASK, VALUE, CONTEXT);
            logconsole(SEP);
        }
#endif
    }
}

void stream_debug(Stream *s) {
    stream_debug_r(s, false);
}
