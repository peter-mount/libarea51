
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

Stream *stream_new() {
    Stream *s = (Stream *) malloc(sizeof (Stream));
    if (s) {
        memset(s, 0, sizeof (Stream));
        s->continueStream = true;
    }
    return s;
}
