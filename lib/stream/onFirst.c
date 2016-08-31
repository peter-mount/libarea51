
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stream-int.h"

struct firstLast {
    void (*action)(StreamData *);
    bool flag;
};

static int onFirstLast(Stream *s, void (*action)(StreamData *), void (*task)(StreamData *d)) {
    if (s && action && task) {
        struct firstLast *ctx = malloc(sizeof (struct firstLast));
        if (ctx) {
            ctx->action = action;
            ctx->flag = false;
            if (stream_invoke(s, task, ctx, free))
                free(ctx);
            else
                return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

static void first(StreamData *d) {
    struct firstLast *ctx = d->task->taskContext;
    if (ctx && !ctx->flag && ctx->action) {
        ctx->flag = true;
        ctx->action(d);
    }

    stream_next(d);
}

int stream_onFirst(Stream *s, void (*action)(StreamData *)) {
    return onFirstLast(s, action, first);
}

static void notFirst(StreamData *d) {
    struct firstLast *ctx = d->task->taskContext;
    if (ctx && ctx->flag && ctx->action)
        ctx->action(d);
    else
        ctx->flag = true;

    stream_next(d);
}

int stream_onNotFirst(Stream *s, void (*action)(StreamData *)) {
    return onFirstLast(s, action, notFirst);
}
