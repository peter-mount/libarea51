/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

int charbuffer_ensure_capacity(CharBuffer *b, int size) {
    if (size > b->size) {
        char *newbuffer = (char *) malloc(size);

        if (!newbuffer)
            return CHARBUFFER_ERROR;

        if (b->buffer) {
            memcpy(newbuffer, b->buffer, b->size);
            free(b->buffer);
        }

        b->size = size;
        b->buffer = newbuffer;
    }
    return CHARBUFFER_OK;
}

/**
 * append some data to a charbuffer. If there's not enough room in the buffer then the buffer will be extended to
 * accomodate the data
 * 
 * @param b     charbuffer
 * @param src   source
 * @param len   length
 * @return 0 if added, 1 if error
 */
int charbuffer_put(CharBuffer *b, char *src, int len) {
    if (!b)
        return CHARBUFFER_ERROR;

    charbuffer_lock(b);

    if (charbuffer_ensure_capacity(b, b->pos + len + 64) == CHARBUFFER_ERROR)
        return CHARBUFFER_ERROR;

    memcpy(b->buffer + b->pos, src, len);
    b->pos += len;

    // Ensure we are terminated
    b->buffer[b->pos] = '\0';

    charbuffer_unlock(b);
    return CHARBUFFER_OK;
}

/**
 * append some data to a charbuffer. If there's not enough room in the buffer then the buffer will be extended to
 * accomodate the data
 * 
 * @param b     charbuffer
 * @param src   source
 * @param len   length
 * @return 0 if added, 1 if error
 */
int charbuffer_add(CharBuffer *b, char c) {
    if (!b)
        return CHARBUFFER_ERROR;

    charbuffer_lock(b);

    // Ensure we have room, but do so in a way we don't keep growing just for 1 character
    charbuffer_ensure_capacity(b, b->pos + (b->pos % 64) + 1);
    b->buffer[b->pos++] = c;

    // Ensure we are terminated
    b->buffer[b->pos] = '\0';

    charbuffer_unlock(b);
    return CHARBUFFER_OK;
}
