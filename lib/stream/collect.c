
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stream-int.h"

static void add(StreamData *d) {
    StreamCollector *ctx = stream_getTaskContext(d);
    if (!ctx)
        return;

    if (ctx->initRequired && ctx->init) {
        ctx->stream = d->task->stream;
        ctx->context = ctx->init(d->task->stream->context);
        ctx->initRequired = false;
    }

    if (ctx->next)
        ctx->next(ctx->context, d->val);
}

static void freeStreamCollector(void *c) {
    if (c) {
        StreamCollector *ctx = c;
        if (ctx->finish)
            ctx->stream->result = ctx->finish(ctx->context);
        free(ctx);
    }
}

/**
 * Add a collector to the stream
 * 
 * @param s Stream
 * @param init initialiser
 * @param next add an item to the collector
 * @param finish finish the collector, returning the result
 * @return 
 */
int stream_collect(Stream *s, void *(*init)(void *), void (*next)(void *, void *), void *(*finish)(void *)) {
    if (s) {
        StreamCollector *ctx = malloc(sizeof (StreamCollector));
        if (ctx) {
            memset(ctx, 0, sizeof (StreamCollector));
            ctx->stream = s;
            ctx->init = init;
            ctx->next = next;
            ctx->finish = finish;
            ctx->initRequired = true;

            if (!stream_invoke(s, add, ctx, freeStreamCollector))
                return EXIT_SUCCESS;

            free(ctx);
        }
    }
    return EXIT_FAILURE;
}
