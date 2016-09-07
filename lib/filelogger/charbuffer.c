#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filelogger-int.h"
#include "../charbuffer/charbuffer-int.h"

static const char NL = '\n';

void filelogger_log_buffer_r(FileLogger *f, CharBuffer *b, int o, int l) {
    if (f && b) {
        charbuffer_lock(b);

        int tl = b->pos - o;
        if (tl > l)
            tl = l;
        if (tl > 0)
            filelogger_log_r(f, b->buffer, o, l);

        charbuffer_unlock(b);
    }
}

void filelogger_log_buffer(FileLogger *f, CharBuffer *b) {
    if (f && b) {
        charbuffer_lock(b);

        if (b->pos)
            filelogger_log_r(f, b->buffer, 0, b->pos);

        charbuffer_unlock(b);
    }
}
