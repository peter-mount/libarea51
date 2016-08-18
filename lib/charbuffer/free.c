/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "area51/charbuffer.h"

void charbuffer_free(CharBuffer *b) {
    if (b->buffer)
        free(b->buffer);
    b->buffer = NULL;
    b->pos = b->size = 0;
}
