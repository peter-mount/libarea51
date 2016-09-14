
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

void *cacheGet(Cache *c, void *k) {
    if (!c || !k)
        return NULL;

    void *v = NULL;
    cacheLock(c);
    {
        struct CacheEntry *e = cacheGetEntry(c, k);

        if (e) {
            v = freeable_get(&e->value);

            // Update expiry time
            if (c->maxage && c->updateTime) {
                time(&e->expires);
                e->expires += c->maxage;
            }

            // LEAST USED move we need to move the entry to the tail of the list
            if (c->maxSize && c->expireLeastUsed && !list_isTail(&e->node)) {
                // Move to the end of the list so when full we remove the least used entry
                list_remove(&e->node);
                list_addTail(&c->list, &e->node);
            }
        }
    }
    cacheUnlock(c);
    return v;
}
