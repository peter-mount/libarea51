
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <area51/charbuffer.h>
#include "../charbuffer-int.h"

void charbuffer_replace(CharBuffer *b, char *k, char *v) {
    if (!b || !k || !v)
        return;

    charbuffer_lock(b);

    int kl = strlen(k);
    int vl = strlen(v);

    int i = 0;
    while (i <= (b->pos - kl)) {
        if (strncmp(&b->buffer[i], k, kl) == 0) {
            charbuffer_ensure_capacity(b, b->pos + vl);
            memmove(&b->buffer[i + vl], &b->buffer[i + kl], b->pos - i - kl + vl);
            memcpy(&b->buffer[i], v, vl);
            b->pos = b->pos - kl + vl;
            i += vl;
        } else
            i++;
    }

    charbuffer_unlock(b);
}

#define INT_LEN 31

void charbuffer_replace_int(CharBuffer *b, char *k, int v) {
    char buf[INT_LEN + 1];
    snprintf(buf, INT_LEN, "%d", v);
    charbuffer_replace(b, k, buf);
}
