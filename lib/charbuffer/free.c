/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

void charbuffer_free(CharBuffer *b) {
    if (b) {
        if (b->buffer)
            free(b->buffer);
        free(b);
    }
}
