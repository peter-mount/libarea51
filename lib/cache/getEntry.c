
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

struct CacheEntry *cacheGetEntry(Cache *c, void *k) {
    struct CacheEntry *e = hashmapGet(c->map, k);
    
    if (e && c->maxage) {
        time_t now;
        time(&now);
        if (e->expires < now) {
            cacheRemoveEntry(c, e);
            return NULL;
        }
    }
    
    return e;
}
