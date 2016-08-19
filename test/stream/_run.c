#include "../tests.h"

extern void test_stream_array(Test *);
extern void test_stream_debug(Test *);
extern void test_stream_collect_summary(Test *);

void test_stream(Test *t) {
    // Test debugging first, if this breaks then it may not help later on
    test_stream_debug(t);
    
    test_stream_array(t);
    test_stream_collect_summary(t);
}
