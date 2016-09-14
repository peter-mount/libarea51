
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

struct CacheEntry *cachePutEntry(Cache *c, void *k) {
    struct CacheEntry *e = malloc(sizeof (struct CacheEntry));
    if (e) {
        memset(e, 0, sizeof (struct CacheEntry));
        e->key = k;

        if (c->lookupConcurrent)
            pthread_mutex_init(&e->mutex, NULL);

        if (c->maxage) {
            time(&e->expires);
            e->expires += c->maxage;
            // Copy so CACHE_EXPIRE_ORIGINAL_TIME will work when CACHE_GET_UPDATE_TIME is in use
            e->original_expires = e->expires;
        }

        list_addTail(&c->list, &e->node);
        hashmapPut(c->map, k, e);
    }
    return e;
}

static void put(Cache *c, void *k, void *v, void (*f)(void*)) {
    if (!k || !v)
        return;

    // Look for existing entry, ignore expiry as we will reset if it exists
    struct CacheEntry *e = hashmapGet(c->map, k);
    if (e) {
        // Existing entry, so update the record rather than remove/free & create a new one

        // Value is the same
        bool same = v == e->value.val && f == e->value.free;

        // CACHE_NO_UPDATE_IF_VALUE_SAME and values are equal then do nothing
        if (c->noUpdateIfSameValue && same)
            return;

        // Update the record rather than remove/free & create a new one

        // Note only set if value not the same as we don't want to free something we should be
        if (!same)
            freeable_set(&e->value, v, f);

        // Update the expiry time
        // Note we force this as it's a new value but we don't change original expires time
        if (c->maxage) {
            time(&e->expires);
            e->expires += c->maxage;
        }

        // Move to the end of the list so when full we remove the least used entry
        // Note we force this as it's a new value
        if (!list_isTail(&e->node)) {
            list_remove(&e->node);
            list_addTail(&c->list, &e->node);
        }
    } else {

        // Are we full? If so remove the least used entry
        if (c->maxSize && hashmapSize(c->map) >= c->maxSize) {
            e = (struct CacheEntry *) list_getHead(&c->list);
            if (e)
                cacheRemoveEntry(c, e);
        }

        // New entry
        e = cachePutEntry(c, k);
        if (e) {
            freeable_set(&e->value, v, f);
        }
    }

}

void cachePut(Cache *c, void *k, void *v, void (*f)(void*)) {
    if (!c || !k)
        return;

    // NULL value then same as remove
    if (!v) {
        cacheRemove(c, k);
        return;
    }

    cacheLock(c);
    put(c, k, v, f);
    cacheUnlock(c);
}

