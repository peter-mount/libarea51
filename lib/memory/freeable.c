#include "freeable-int.h"

/*
 * Freeable - a freeable value.
 * 
 * This came into being because I was repeating this exact pattern too many times
 * in other code.
 * 
 * To use:
 * 
 * Freeable *f = freeable_new(value,free);
 * 
 * Pass on to some other method.
 * 
 * When it comes to freeing some state it can then call:
 * 
 * freeable_free(f);
 * 
 * If the original free parameter to new was not null then that method is called
 * to free the value.
 * 
 * Also, during the lifetime of the Freeable you can use freeable_set to replace
 * the value. When replacing it, if the old value is not null and free was set
 * then it's called to free the value.
 * 
 */

Freeable *freeable_new(void *v, void (*f)(void *)) {
    Freeable *ret = malloc(sizeof (struct Freeable));
    if (ret) {
        ret->val = v;
        ret->free = f;
    }
    return ret;
}

void freeable_clear(Freeable *f) {
    if (f) {
        if (f->val && f->free)
            f->free(f->val);
    }
}

void freeable_free(Freeable *f) {
    if (f) {
        freeable_clear(f);
        free(f);
    }
}

void *freeable_get(Freeable *f) {
    return f ? f->val : NULL;
}

Freeable *freeable_set(Freeable *f, void *v, void (*vf)(void *)) {
    if (f) {
        if (f->val && f->free)
            f->free(f->val);
        f->val = v;
        f->free = vf;
        return f;
    }
    return freeable_new(v, vf);
}
