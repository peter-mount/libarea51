/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "area51/charbuffer.h"

void charbuffer_appendbuffer(CharBuffer *dest, CharBuffer *src) {
    if (0 == pthread_mutex_lock(&src->mutex)) {
        charbuffer_put(dest, src->buffer, src->pos);
        pthread_mutex_unlock(&src->mutex);
    }
}
