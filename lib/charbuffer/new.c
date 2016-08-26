/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "charbuffer-int.h"

CharBuffer *charbuffer_new() {
    CharBuffer * b = malloc(sizeof (struct charbuffer));
    if (b) {
        memset(b, 0, sizeof (struct charbuffer));

        b->size = CHARBUFFER_INITIAL_SIZE;
        b->buffer = malloc(CHARBUFFER_INITIAL_SIZE);
        if (!b->buffer) {
            free(b);
            return NULL;
        }

        b->pos = 0;

        pthread_mutex_init(&b->mutex, NULL);
    }
    return b;
}
