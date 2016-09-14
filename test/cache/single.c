/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include "area51/hashmap.h"
#include <area51/cache.h>
#include <area51/trace.h>

void test_cache_single(Test *t) {

    char *key[20];
    char *val[20];

    trace;
//    Cache *cache = cacheCreate(10, 0, hashmapStringHash, hashmapStringEquals, free, free);
    Cache *cache = cacheCreate(10, 0, hashmapStringHash, hashmapStringEquals, NULL,NULL);
    trace;
    assertNonNull(t, cache);

    trace;
    for (int i = 0; i < 9; i++) {
        // The key
        trace;
        key[i] = malloc(32);
        assertNonNull(t, key[i]);
        snprintf(key[i], 9, "k%d", i);

        // Value
        trace;
        val[i] = malloc(32);
        assertNonNull(t, val[i]);
        snprintf(val[i], 9, "v%d", i);

        trace;
        logconsole("Insert \"%s\"=\"%s\"", key[i], val[i]);
        cachePut(cache, key[i], val[i]);
    }

    trace;
    logconsole("size %d",cacheSize(cache) );
    //assertTrue(t, cacheSize(cache) == 10);

    trace;
    cacheFree(cache);

    trace;
    pass(t);
}
