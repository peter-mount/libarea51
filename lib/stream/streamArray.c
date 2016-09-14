#include <stdlib.h>
#include <area51/stream.h>
#include <string.h>
#include <area51/log.h>
#include "stream-int.h"

struct ctx {
    void **array;
    long pos;
    long size;
};

static void setVal(StreamData *d) {
    struct ctx *ctx = stream_getTaskContext(d);

    stream_setVal(d, ctx->array[ctx->pos], NULL);
    ctx->pos++;

    stream_next(d);

    if (ctx->pos >= ctx->size)
        stream_terminate(d);
}

Stream *stream_array(void **array, long size) {

    // Singleton instance?
    if (size == 1)
        return stream_of(*array, NULL);

    struct ctx *ctx = malloc(sizeof (struct ctx));
    if (!ctx)
        return NULL;

    ctx->array = array;
    ctx->pos = 0;
    ctx->size = size;

    Stream * s = stream_new();
    if (s) {
        if (stream_invoke(s, setVal, ctx, free)) {
            stream_free(s);
            free(ctx);
            return NULL;
        }
    }
    return s;
}
