#include <stdlib.h>
#include <string.h>
#include <area51/stream.h>
#include "hashmap-int.h"

/*
 * Returns a Stream which provides KeyValue instances for each Key/Value pair
 * within a Hashmap.
 * 
 * For example, create a stream, map it so we look just at values,
 * then filter for values that equal some value and then run a consumer against
 * any found.
 * 
 * Stream *stream = hashmapStream(map);
 * stream_map(stream, map_keyValue_value);
 * stream_equal(map, value, NULL );
 * stream_forEach(stream, consumer );
 * 
 */
struct ctx {
    size_t i;
    Hashmap *map;
    Entry *entry;
};

static void loop(StreamData *d) {
    struct ctx *ctx = stream_getTaskContext(d);

    if (ctx->entry) {
        Entry *next = ctx->entry->next;

        KeyValue *val = malloc(sizeof (KeyValue));
        if (!val) {
            stream_terminate(d);
            return;
        }

        val->key = ctx->entry->key;
        val->value = ctx->entry->value;

        stream_setVal(d, val, free);
        stream_next(d);

        // This will free the KeyValue if it's not already been freed
        stream_setVal(d, NULL, NULL);

        ctx->entry = next;
    } else if (ctx->i < ctx->map->bucketCount) {
        ctx->entry = ctx->map->buckets[ctx->i];
        ctx->i++;
    } else
        stream_terminate(d);
}

Stream *hashmapStream(Hashmap *map) {
    Stream *s = stream_new();
    if (s) {
        struct ctx *ctx = malloc(sizeof (struct ctx));
        if (!ctx) {
            stream_free(s);
            return NULL;
        }

        memset(ctx, 0, sizeof (struct ctx));
        ctx->i = 0;
        ctx->map = map;

        if (stream_invoke(s, loop, ctx, free)) {
            free(ctx);
            stream_free(s);
            return NULL;
        }
    }
    return s;
}