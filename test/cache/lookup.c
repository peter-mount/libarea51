/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include <unistd.h>
#include "../tests.h"
#include "area51/hashmap.h"
#include <area51/cache.h>
#include <string.h>

static void lookup(void *k, void *c, Freeable *f) {
    int l = strlen((char *) k) + 2;
    char *s = malloc(l + 1);
    if (s) {
        snprintf(s, l, "v%s", k);
        freeable_set(f, s, free);
    }
}

void test_cache_lookup(Test *t) {
    startTest(t);

    // Max size 10
    int maxSize = 10;

    // Max age 5s
    time_t maxAge = 500;

    // Create the cache. We want to expire when full the least used entries
    Cache *cache = cacheCreate(maxSize,
            maxAge,
            hashmapStringHash, hashmapStringEquals, NULL,
            CACHE_EXPIRE_LEAST_USED,
            // lookup
            lookup, NULL, NULL
            );

    assertNonNull(t, cache);

    void *v = cacheGet(cache, "k5");
    assertNonNull(t, v);
    assertTrue(t, strcmp((char *) v, "vk5") == 0);

    cacheFree(cache);

    pass(t);
}
