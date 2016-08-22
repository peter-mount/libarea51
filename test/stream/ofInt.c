/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include <area51/log.h>
#include <area51/list.h>
#include <area51/stream.h>

#define TEST_VALUE 42

static int result = INT_MIN;

static void forEach(StreamData *d) {
    result = stream_void_int(stream_getVal(d));
}

void test_stream_ofInt(Test *t) {
    startTest(t);

    Stream *s = stream_of_int(TEST_VALUE);

    int r = s ? EXIT_SUCCESS : EXIT_FAILURE;

    if (!r)
        r = stream_forEach(s, forEach);

    if (!r) {
        result = INT_MIN;
        //stream_debug(s);
        stream_run(s, NULL);
        
        assertTrue(t,result==TEST_VALUE);
        
        pass(t);
    } else {
        stream_free(s);
        fail(t);
    }
}
