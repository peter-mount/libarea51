
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
        unsigned int flags
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
    c->flags = flags;
    
    // Update time implies least used mode as we need to move the entry to the
    // top of the list
    if(c->flags & CACHE_GET_UPDATE_TIME)
        c->flags |= CACHE_EXPIRE_LEAST_USED;
    
    return c;
}