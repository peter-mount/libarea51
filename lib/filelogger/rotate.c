#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <area51/file.h>
#include "filelogger-int.h"

void filelogger_rotate(FileLogger *f) {
    if (!f)
        return;

    time(&f->time);
    gmtime_r(&f->time, &f->tm);

    bool close = false;
    if (f->f) {
        switch (f->rotate) {
            case FILELOGGER_ROTATE_DAY:
                close = f->tm.tm_mday != f->last;
                break;

            case FILELOGGER_ROTATE_MINUTE:
                close = f->tm.tm_min != f->last;
                break;

            case FILELOGGER_ROTATE_HOUR:
            default:
                close = f->tm.tm_hour != f->last;
                break;
        }
    }

    if (close && f->f) {
        fclose(f->f);
        f->f = NULL;
    }

    if (!f->f) {
        int v = f->tm.tm_hour;
        charbuffer_reset(f->b);

        charbuffer_append(f->b, f->directory);
        charbuffer_add(f->b, '/');

        charbuffer_append_int(f->b, f->tm.tm_year + 1900, 0);
        charbuffer_add(f->b, '/');

        charbuffer_append_int(f->b, f->tm.tm_mon + 1, 0);

        if (f->rotate == FILELOGGER_ROTATE_DAY) {
            v = f->tm.tm_mday;
        } else {
            charbuffer_add(f->b, '/');
            charbuffer_append_int(f->b, f->tm.tm_mday, 0);

            if (f->rotate == FILELOGGER_ROTATE_HOUR) {
                v = f->tm.tm_hour;
            } else {
                charbuffer_add(f->b, '/');
                charbuffer_append_int(f->b, f->tm.tm_hour, 0);
                v = f->tm.tm_min;
            }
        }

        int len;
        char * p = charbuffer_tostring(f->b, &len);
        mkdirs(p, 0755);
        free(p);

        charbuffer_add(f->b, '/');

        if (f->prefix)
            charbuffer_append(f->b, f->prefix);

        charbuffer_append_int(f->b, v, 0);

        if (f->suffix)
            charbuffer_append(f->b, f->suffix);

        if (f->path)
            free(f->path);
        f->path = charbuffer_tostring(f->b, &len);
        f->f = fopen(f->path, "a");

        f->last = v;
    }
}