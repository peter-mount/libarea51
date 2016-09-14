
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stream-int.h"

struct ctx {
    bool(*filter)(void *, void *);
    void *context;
    void (*freeContext)(void *);
};

static void filter(StreamData *d) {
    struct ctx *ctx = stream_getTaskContext(d);
    if (ctx && ctx->filter) {
        if (ctx->filter(d->val, ctx->context))
            stream_next(d);
    } else
        // No filter so abort the stream
        stream_terminate(d);
}

static void freeFilter(void *c) {
    struct ctx *ctx = c;
    if (ctx) {
        if (ctx->freeContext)
            ctx->freeContext(ctx->context);
        free(ctx);
    }
}

int stream_filter_r(Stream *s, bool(*f)(void *, void *), void *c, void (*fc)(void *), const char *n) {
    struct ctx *ctx = malloc(sizeof (struct ctx));
    if (ctx) {
        memset(ctx, 0, sizeof (struct ctx));
        ctx->filter = f;
        ctx->context = c;
        ctx->freeContext = fc;
        return stream_invoke_r(s, filter, ctx, freeFilter, n);
    }
    return EXIT_FAILURE;
}

int stream_filter(Stream *s, bool(*f)(void *, void *), void *c, void (*free)(void *)) {
    return stream_filter_r(s, f, c, free, __PRETTY_FUNCTION__);
}

static bool equal(void *v, void *c) {
    return v == c;
}

static bool notEqual(void *v, void *c) {
    return v != c;
}

int stream_equal(Stream *s, void *v, void (*f)(void *)) {
    return stream_filter_r(s, equal, v, f, __PRETTY_FUNCTION__);
}

int stream_notEqual(Stream *s, void *v, void (*f)(void *)) {
    return stream_filter_r(s, notEqual, v, f, __PRETTY_FUNCTION__);
}

int stream_notNull(Stream *s) {
    return stream_filter_r(s, notEqual, NULL, NULL, __PRETTY_FUNCTION__);
}
