/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include <area51/stream.h>

#define TEST_SIZE 5

static char *TEST_DATA[] = {
    "a", "b", "c", "d", "e"
};

static void next(void *c, void *v) {
    void **p = c;
    *p = v;
}

static void *finish(void *c) {
    void **p = c;
    return *p;
}

void test_stream_collect_summary(Test *t) {
    void *result = NULL;

    startTest(t);

    Stream *s = stream_array((void**) TEST_DATA, TEST_SIZE);
    assertNonNull(t, s);

    //stream_debug(s);

    assertSuccess(t, stream_collect(s, NULL, next, finish, &result, NULL));

    void *r = stream_run(s, NULL);
    assertNonNull(t, r);

    assertTrueM(t, r == TEST_DATA[TEST_SIZE - 1], "Wrong value returned");

    pass(t);
}
