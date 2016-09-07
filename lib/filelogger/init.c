#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filelogger-int.h"

FileLogger *filelogger_new(char *d, char *p, char *s, int r) {
    if (!d || !r)
        return NULL;

    FileLogger * l = malloc(sizeof (struct FileLogger));
    if (l) {
        memset(l, 0, sizeof (struct FileLogger));
        pthread_mutex_init(&l->mutex, NULL);
        l->b = charbuffer_new();
        l->directory = d;
        l->prefix = p;
        l->suffix = s;
        l->rotate = r;
    }
    return l;
}

FileLogger *filelogger_new_json(struct json_object *o) {
    char *d = json_getString(o, "directory");
    char *s = json_getString(o, "rotate");
    if (!d || !s)
        return NULL;

    int r = 0;
    if (strcasecmp(s, "minute") == 0)
        r = FILELOGGER_ROTATE_MINUTE;
    else
        if (strcasecmp(s, "hour") == 0)
        r = FILELOGGER_ROTATE_HOUR;
    else
        if (strcasecmp(s, "day") == 0)
        r = FILELOGGER_ROTATE_DAY;
    else
        r = FILELOGGER_ROTATE_HOUR;

    d = strdup(d);

    char *p = json_getString(o, "prefix");
    if (p)
        p = strdup(p);

    s = json_getString(o, "suffix");
    if (s)
        s = strdup(s);

    return filelogger_new(d, p, s, r);
}