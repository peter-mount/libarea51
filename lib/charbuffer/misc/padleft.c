
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "area51/charbuffer.h"

int charbuffer_append_padleft(CharBuffer *b, char *src, int width) {
    int l = strlen(src);
    if (l > width)
        l = width;
    
    int i = width - l;
    while (i>0) {
        charbuffer_add(b, ' ');
        i--;
    }

    return charbuffer_put(b, src, l);
}

