#include <stdlib.h>
#include <area51/stream.h>
#include <string.h>
#include <area51/log.h>
#include "../../libarea51/lib/stream/stream-int.h"

static void link(StreamData *d) {
    StreamData *parent = d->task->taskContext;

    StreamData *child = malloc(sizeof (StreamData));
    if (child) {
        memset(child, 0, sizeof (StreamData));
        child->val = d->val;

        // Never free d->val as that's owned by the parent
        child->free = NULL;

        child->task = parent->task->next;
        child->task->action(child);

        if (child->val && child->free)
            child->free(child->val);

        free(child);
    }
}

struct ctx {
    Stream *(*mapper)(StreamData *, void *);
    void *c;
};

static void flatMap(StreamData *d) {
    struct ctx *ctx = stream_getTaskContext(d);

    // No context or null data then stop here, no data to flatMap
    if (!ctx || !stream_getVal(d))
        return;

    Stream *s = ctx->mapper(d, ctx->c);

    if (s) {
        if (stream_invoke(s, link, d, NULL)) {
            stream_free(s);
            return;
        }

        if (d->task->stream->debug)
            stream_debug_r(s, true);

        stream_run(s, NULL);
    }
}

int stream_flatMap(Stream *s, Stream *(*mapper)(StreamData *d, void *c), void *c) {
    struct ctx *ctx = malloc(sizeof (struct ctx));
    if (!ctx)
        return EXIT_FAILURE;

    memset(ctx, 0, sizeof (struct ctx));
    ctx->mapper = mapper;
    ctx->c = c;
    if (stream_invoke(s, flatMap, ctx, free)) {
        free(ctx);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}