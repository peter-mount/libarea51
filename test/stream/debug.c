#include "../tests.h"

#include <area51/stream.h>

#define TEST_SIZE 5

static char *TEST_DATA[] = {
    "a", "b", "c", "d", "e"
};

static void forEach(StreamData *d) {
    //logconsole("Received %s", stream_getVal(d));
}

void test_stream_debug(Test *t) {
    startTest(t);

    Stream *s = stream_array((void**) TEST_DATA, TEST_SIZE);
    assertNonNull(t,s);

    assertSuccess(t, stream_forEach(s, forEach) );

    stream_debug(s);
    stream_run(s, NULL);

    pass(t);
}
