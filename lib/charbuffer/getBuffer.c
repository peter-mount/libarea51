#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

/*
 * Returns the underlying buffer, removing it from the CharBuffer.
 * 
 * Once returned the caller must use free(void*) to free the buffer.
 *
 * @param b CharBuffer
 * @param len Pointer to int to store the buffer size
 * @return the original underlying buffer, NULL if none or b was null
 */
void *charbuffer_getBuffer(CharBuffer *b, int *len) {
    if (!b)
        return NULL;

    charbuffer_lock(b);

    *len = b->pos;
    void *ret = b->buffer;
    b->pos = b->size = 0;
    b->buffer = NULL;

    charbuffer_unlock(b);
    return ret;
}
