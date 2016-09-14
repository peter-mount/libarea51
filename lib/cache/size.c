
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

size_t cacheSize(Cache *c) {
    if (!c)
        return 0;

    size_t s = 0;

    cacheLock(c);
    {
        cacheExpireIntl(c);
        s = hashmapSize(c->map);
    }
    cacheUnlock(c);

    return s;
}
