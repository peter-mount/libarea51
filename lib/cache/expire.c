
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

/**
 * Internal (does not lock) entry point for expiring entries from a cache
 * @param c
 */
void cacheExpireIntl(Cache *c) {
    if (c && c->maxage) {
        // Check for expiry of oldest entries and expire them
        Node *n = list_getHead(&c->list);
        if (list_isNode(n)) {
            time_t now;
            time(&now);

            while (list_isNode(n) && ((struct CacheEntry *) n)->expires < now) {
                struct CacheEntry *e = (struct CacheEntry *) n;
                n = list_getNext(n);
                cacheRemoveEntry(c, e);
            }
        }
    }
}

/**
 * Public entry point to expire a cache
 * @param c
 */
void cacheExpire(Cache *c) {
    if (c) {
        cacheLock(c);
        cacheExpireIntl(c);
        cacheUnlock(c);
    }
}
