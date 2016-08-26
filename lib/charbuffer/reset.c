/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

/**
 * Resets a buffer so new data can be appended to it using the existing buffer.
 * @param b charbuffer
 * @return 0 if reset, 1 if error
 */
void charbuffer_reset(CharBuffer *b) {
    charbuffer_lock(b);
    b->pos = 0;
    charbuffer_unlock(b);
}
