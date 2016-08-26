/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

void charbuffer_appendbuffer(CharBuffer *dest, CharBuffer *src) {
    if (dest && src) {
        charbuffer_lock(src);
        charbuffer_put(dest, src->buffer, src->pos);
        charbuffer_unlock(src);
    }
}
