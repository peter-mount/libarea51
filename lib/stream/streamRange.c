#include <stdlib.h>
#include <area51/stream.h>
#include <string.h>
#include <area51/log.h>
#include "stream-int.h"

struct ctx {
    long start;
    long end;
    long inc;
    long val;
};

static void setVal(StreamData *d) {
    struct ctx *ctx = stream_getTaskContext(d);

    stream_setVal(d, (void *)ctx->val, NULL);
    ctx->val += ctx->inc;

    stream_next(d);

    if (ctx->start < ctx->end && ctx->val > ctx->end)
        stream_terminate(d);
    else if (ctx->start > ctx->end && ctx->val < ctx->end)
        stream_terminate(d);
}

Stream *stream_range_r(long start, long end, long inc) {
    // If start and end the same then use singleton method
    if (start == end)
        return stream_of((void *) start, NULL);

    struct ctx *ctx = malloc(sizeof (struct ctx));
    if (!ctx)
        return NULL;

    ctx->start = ctx->val = start;
    ctx->end = end;

    if (start < end)
        ctx->inc = inc == 0 ? 1 : inc < 0 ? -inc : inc;
    else
        ctx->inc = inc == 0 ? -1 : inc > 0 ? -inc : inc;

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

Stream *stream_range(long start, long end) {
    return stream_range_r(start, end, start < end ? 1 : -1);
}
