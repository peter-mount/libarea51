#include "../tests.h"

extern void test_stream_array(Test *);
extern void test_stream_debug(Test *);

extern void test_stream_collect_findFirst(Test *);
extern void test_stream_collect_summary(Test *);

extern void test_stream_findFirst(Test *);

extern void test_stream_flatMap(Test *);
extern void test_stream_findFirst_flatMap(Test *);

extern void test_stream_ofInt(Test *);

void test_stream(Test *t) {
    // Test debugging first, if this breaks then it may not help later on
    test_stream_debug(t);

    test_stream_array(t);

    test_stream_collect_findFirst(t);
    test_stream_collect_summary(t);

    test_stream_findFirst(t);

    test_stream_flatMap(t);
    test_stream_findFirst_flatMap(t);

    test_stream_ofInt(t);
}
