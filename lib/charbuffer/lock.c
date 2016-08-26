#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

void charbuffer_lock(CharBuffer *b) {
    if (b)
        pthread_mutex_lock(&b->mutex);
}

void charbuffer_unlock(CharBuffer *b) {
    if (b)
        pthread_mutex_unlock(&b->mutex);
}
