
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

void cacheRemove(Cache *c, void *k) {
    if (!c || !k)
        return;

    cacheLock(c);
    {
        struct CacheEntry *e = hashmapGet(c->map, k);
        if (e)
            cacheRemoveEntry(c, e);
    }
    cacheUnlock(c);
}
