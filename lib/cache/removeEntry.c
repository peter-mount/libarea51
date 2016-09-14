
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

void cacheRemoveEntry(Cache *c, struct CacheEntry *e) {
    if (c && e) {
        hashmapRemove(c->map, e->key);
        list_remove(&e->node);

        if (c->freeKey)
            c->freeKey(e->key);

        if (c->freeValue)
            c->freeValue(e->value);

        free(e);
    }
}
