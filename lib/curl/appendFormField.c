
#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <area51/charbuffer.h>
#include "../charbuffer/charbuffer-int.h"

int charbuffer_append_form_field(CharBuffer *b, char *name, char *value) {
    int ret = CHARBUFFER_OK;

    if (b->pos)
        ret = charbuffer_add(b, '&');

    if (!ret)
        ret = charbuffer_append(b, name);

    if (!ret)
        ret = charbuffer_add(b, '=');

    if (!ret)
        ret = charbuffer_append_urlencode(b, value);

    return ret;
}
