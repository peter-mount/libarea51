#include "../tests.h"

extern void test_stream_array(Test *);
extern void test_stream_collect_summary(Test *);

void test_stream(Test *t) {
    test_stream_array(t);
    test_stream_collect_summary(t);
}
