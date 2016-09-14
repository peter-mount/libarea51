
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

void cacheRemoveIf(Cache *c, bool(*p)(void *k, void *v)) {
    if (!c || !p)
        return;

    cacheLock(c);
    {
        Node *n = list_getHead(&c->list);
        while (list_isNode(n)) {
            struct CacheEntry *e = (struct CacheEntry *) n;
            n = list_getNext(n);

            if (p(e->key, e->value.val))
                cacheRemoveEntry(c, e);
        }
    }
    cacheUnlock(c);
}
