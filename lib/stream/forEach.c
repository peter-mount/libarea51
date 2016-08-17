
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

int stream_forEach(Stream *s, void (*consumer)(StreamData *)) {
    return stream_invoke(s, consumer, NULL, NULL);
}
