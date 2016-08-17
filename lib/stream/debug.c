
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <area51/log.h>
#include "stream-int.h"

void stream_debug(Stream *s) {
    logconsole("Stream %lx", s);
    if (s) {
        StreamTask *t = s->start;
        int c = 0;
        while (t) {
            logconsole("StreamTask %02d %lx ctx %lx next  %lx", ++c, t, t->taskContext, t->next);
            t = t->next;
        }
        logconsole("%d tasks", c);
        s->debug = true;
    }
}
