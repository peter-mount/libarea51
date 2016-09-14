
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
            v = e->value;

            // Move to the end of the list so when full we remove the least used entry
            if (!list_isTail(&e->node)) {
                list_remove(&e->node);
                list_addTail(&c->list, &e->node);
            }
        }
    }
    cacheUnlock(c);
    return v;
}
