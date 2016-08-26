/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

/**
 * Returns the size of data currently in the charbuffer
 * 
 * @param b charbuffer
 * @return the size, -1 if the lock cannot be obtained
 */
int charbuffer_size(CharBuffer *b) {
    int ret = -1;
    charbuffer_lock(b);
    // pos is the append point so to the client the size of data present!
    ret = b->pos;
    charbuffer_unlock(b);
    return ret;
}
