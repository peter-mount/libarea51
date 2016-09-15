
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

Cache *cacheCreate(
        size_t maxSize,
        time_t maxage,
        int (*hash)(void* key),
        bool(*equals)(void* keyA, void* keyB),
        void (*fk)(void *),
        unsigned int flags,
        void (*lookup)(void *, void *, Freeable *),
        void *lookupContext,
        void (*lookupFree)(void *)
        ) {
    Cache *c = malloc(sizeof (struct Cache));
    if (!c)
        return NULL;

    memset(c, 0, sizeof (struct Cache));

    c->map = hashmapCreate(10, hash, equals);
    if (!c->map) {
        free(c);
        return NULL;
    }

    list_init(&c->list);

    pthread_mutex_init(&c->mutex, NULL);

    c->maxage = maxage;
    c->maxSize = maxSize;
    c->freeKey = fk;

    c->updateTime = (flags & CACHE_GET_UPDATE_TIME) != 0;
    c->expireLeastUsed = (flags & CACHE_EXPIRE_LEAST_USED) != 0;
    c->expireOriginalTime = (flags & CACHE_EXPIRE_ORIGINAL_TIME) != 0;
    c->noUpdateIfSameValue = (flags & CACHE_NO_UPDATE_IF_VALUE_SAME) != 0;
    c->lookupConcurrent = (flags & CACHE_LOOKUP_CONCURRENT) != 0;

    // Update time implies least used mode as we need to move the entry to the top of the list
    if (c->updateTime)
        c->expireLeastUsed = 1;

    c->lookup = lookup;
    if (lookupContext)
        freeable_set(&c->lookupContext, lookupContext, lookupFree);

    return c;
}