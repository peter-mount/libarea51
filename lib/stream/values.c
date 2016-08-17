
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

/*
 * Retrieve the current value
 */
void *stream_getVal(StreamData *d) {
    return d ? d->val : NULL;
}

/*
 * Set the current value
 * 
 * @param d StreamData
 * @param v value to set
 * @param f method to free v if required, ignored if NULL
 */
void stream_setVal(StreamData *d, void *v, void *f) {
    if (d) {
        if (d->val && d->free)
            d->free(d->val);
        d ->val = v;
        d->free = f;
    }
}
