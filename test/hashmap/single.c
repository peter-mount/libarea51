/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include "area51/hashmap.h"
#include <area51/cache.h>

void test_hashmap_single(Test *t) {

    char *key[20];
    char *val[20];

    Hashmap *cache = hashmapCreate(10, hashmapStringHash, hashmapStringEquals);
    assertNonNull(t, cache);

    for (int i = 0; i < 10; i++) {
        // The key
        key[i] = malloc(10);
        assertNonNull(t, key[i]);
        snprintf(key[i], 9, "k%d", i);

        // Value
        val[i] = malloc(10);
        assertNonNull(t, val[i]);
        snprintf(val[i], 9, "v%d", i);

        hashmapPut(cache, key[i], val[i]);
    }

    assertTrue(t, hashmapSize(cache) == 10);

   // hashmapFree(cache);

    pass(t);
}
