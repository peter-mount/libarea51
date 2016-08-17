
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

static void findFirst(StreamData *d) {
    stream_next(d);
    stream_terminate(d);
}

int stream_findFirst(Stream *s) {
    return stream_invoke(s, findFirst, NULL, NULL);
}
