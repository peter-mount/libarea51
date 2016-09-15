#include "../tests.h"

extern void test_cache_single(Test *);
extern void test_cache_get(Test *);
extern void test_cache_lookup(Test *);

void test_cache(Test *t) {
    test_cache_single(t);
    test_cache_get(t);
    test_cache_lookup(t);
}
