
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

struct ctx {
    long limit;
    long count;
};

static void action(StreamData *d) {
    struct ctx *ctx = stream_getTaskContext(d);
    stream_next(d);

    ctx->count++;

    if (ctx->count >= ctx->limit)
        stream_terminate(d);
}

int stream_limit(Stream *s, long limit) {
    struct ctx *ctx = malloc(sizeof (struct ctx));
    if (ctx) {
        ctx->limit = limit;
        ctx->count = 0;
        return stream_invoke(s, action, ctx, free);
    }
    return EXIT_FAILURE;
}
