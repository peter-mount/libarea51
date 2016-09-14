
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

void cacheFree(Cache *c) {
    if (!c)
        return;

    cacheRemoveAll(c);

    hashmapFree(c->map);

    freeable_clear(&c->lookupContext);

    free(c);
}
