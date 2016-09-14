
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "cache-int.h"

void cacheLock(Cache *c) {
    if (c)
        pthread_mutex_lock(&c->mutex);
}

void cacheUnlock(Cache *c) {
    if (c)
        pthread_mutex_unlock(&c->mutex);
}
