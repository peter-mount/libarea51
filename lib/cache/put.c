
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>
#include <area51/trace.h>

#include "cache-int.h"

static void put(Cache *c, void *k, void *v) {
    if (!k || !v)
        return;

    // Look for existing entry, ignore expiry as we will reset if it exists
    struct CacheEntry *e = hashmapGet(c->map, k);
    if (e) {
        logconsole("existing %s", k);
        // Existing entry
        if (c->freeValue)
            c->freeValue(e->value);

        e->value = v;

        // Update the expiry time
        if (c->maxage) {
            time(&e->expires);
            e->expires += c->maxage;
        }

        // Move to the end of the list so when full we remove the least used entry
        if (!list_isTail(&e->node)) {
            list_remove(&e->node);
            list_addTail(&c->list, &e->node);
        }
    } else {
        // New entry
        trace;

        // Are we full? If so remove the least used entry
        if (c->maxSize && hashmapSize(c->map) >= c->maxSize) {
            trace;
            e = (struct CacheEntry *) list_getHead(&c->list);
            if (e)
                cacheRemoveEntry(c, e);
            trace;
        }

        trace;
        e = malloc(sizeof (struct CacheEntry));
        if (e) {
            trace;
            memset(e, 0, sizeof (struct CacheEntry));
            e->key = k;
            e->value = v;

            trace;
            if (c->maxage) {
                time(&e->expires);
                e->expires += c->maxage;
            }

            logconsole("new %lx %s %lx", c->map, k, e);
            trace;
            list_addTail(&c->list, &e->node);
            trace;
            hashmapPut(c->map, k, e);
            trace;
        }
    }
    trace;

}

void cachePut(Cache *c, void *k, void *v) {
    if (!c || !k)
        return;

    // NULL value then same as remove
    if (!v) {
        cacheRemove(c, k);
        return;
    }

    cacheLock(c);
    put(c, k, v);
    cacheUnlock(c);
}

