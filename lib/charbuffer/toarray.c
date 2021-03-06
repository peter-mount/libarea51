/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

/**
 * Returns a new array containing the buffer's content.
 * 
 * It is up to the application to free the returned array
 * 
 * @param b charbuffer
 * @return array containing the buffer content, null on error
 */

void *charbuffer_toarray(CharBuffer *b, int *len) {
    charbuffer_lock(b);

    *len = b->pos;

    void *ret = malloc(b->pos);
    if (ret && b->pos)
        memcpy(ret, b->buffer, b->pos);

    charbuffer_unlock(b);
    return ret;
}
