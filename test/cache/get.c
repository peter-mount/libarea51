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

static void put(Test *t, Cache *cache, int s, int e) {
    logconsole("Insert %d..%d", s, e - 1);
    for (int i = s; i < e; i++) {
        // The key
        void *key = malloc(32);
        assertNonNull(t, key);
        snprintf(key, 9, "k%d", i);

        // Value
        char *val = malloc(32);
        assertNonNull(t, val);
        snprintf(val, 9, "v%d", i);

        cachePut(cache, key, val, free);
    }
}

void test_cache_get(Test *t) {
    startTest(t);
    
    // Max size 10
    int maxSize = 10;

    // Max age 5s
    time_t maxAge = 500;

    // Create the cache. We want to expire when full the least used entries
    Cache *cache = cacheCreate(maxSize,
            maxAge,
            hashmapStringHash, hashmapStringEquals, free,
            CACHE_EXPIRE_LEAST_USED,
            // No lookup
            NULL, NULL, NULL
            );

    assertNonNull(t, cache);

    // Fill the cache
    put(t, cache, 0, maxSize);

    // Should be maxSize
    assertTrue(t, cacheSize(cache) == maxSize);

    void *v = cacheGet(cache, "k5");
    assertNonNull(t, v);
    assertTrue(t, strcmp((char *) v, "v5") == 0);

    cacheFree(cache);

    pass(t);
}
