
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

void cacheRemoveAll(Cache *c) {
    if (!c)
        return;

    cacheLock(c);
    {
        Node *n = list_getHead(&c->list);
        while (list_isNode(n)) {
            struct CacheEntry *e = (struct CacheEntry *) n;
            n = list_getNext(n);
            cacheRemoveEntry(c, e);
        }
    }
    cacheUnlock(c);
}
