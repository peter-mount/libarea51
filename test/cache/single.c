/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include "area51/hashmap.h"
#include <area51/cache.h>

static void sleep_quarter_second() {
    struct timespec ts;
    ts.tv_nsec = 250000000;
    ts.tv_sec = 0;
    nanosleep(&ts, NULL);
}

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

        sleep_quarter_second();
    }
}

void test_cache_single(Test *t) {

    // Max size 10
    int maxSize = 10;

    // Max age 5s
    time_t maxAge = 5;

    // Create the cache. We want to expire when full the least used entries
    Cache *cache = cacheCreate(maxSize,
            maxAge,
            hashmapStringHash, hashmapStringEquals, free,
            CACHE_EXPIRE_LEAST_USED);

    assertNonNull(t, cache);

    // Fill the cache
    put(t, cache, 0, maxSize);

    // Should be maxSize
    assertTrue(t, cacheSize(cache) == maxSize);

    // Add one more, should remove oldest so still maxSize
    put(t, cache, maxSize, maxSize + 1);

    // Should still be maxSize
    assertTrue(t, cacheSize(cache) == maxSize);

    // Should remove some entries
    sleep(maxAge - 1);

    // Should have some expired now, give some allowance on the result
    assertTrue(t, cacheSize(cache) >= 5 || cacheSize(cache) <= 7);

    // Add another lot. The first one should also replace an existing entry
    put(t, cache, maxSize, maxSize * 2);

    // Should now be full, i.e. maxSize
    assertTrue(t, cacheSize(cache) == maxSize);

    cacheFree(cache);

    pass(t);
}
