
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
        void (*fv)(void *)
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
    c->freeValue = fv;

    return c;
}