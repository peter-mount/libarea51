/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include <area51/log.h>
#include <area51/list.h>
#include <area51/stream.h>

#define TEST_SIZE 5

static char *TEST_DATA0[] = {"a", "b", "c", "d", "e"};

static char *TEST_DATA1[] = {"f", "g", "h", "i", "j"};

static struct List *list = NULL;

static int ctr;

static void next(void *c, void *v) {
    void **p = c;
    *p = v;
    ctr++;
}

static void *finish(void *c) {
    void **p = c;
    return *p;
}

static Stream *flatMap(StreamData *d, void *c) {
    //Stream *s=stream_array((void**) TEST_DATA1, TEST_SIZE);

    Stream *s = list_stream(list);
    list_map_node_name(s);
    return s;
}

void test_stream_flatMap(Test *t) {
    startTest(t);

    logconsole("Creating shared list");
    list = malloc(sizeof (List));
    list_init(list);
    for (int i = 0; i < TEST_SIZE; i++)
        list_addTail(list, node_alloc(TEST_DATA1[i]));

    for (int pass = 0; pass < 3; pass++) {
        logconsole("Running pass %d", pass + 1);

        void *result = NULL;
        ctr = 0;

        Stream *s = stream_array((void**) TEST_DATA0, TEST_SIZE);
        assertNonNull(t, s);

        assertSuccess(t, stream_flatMap(s, flatMap, NULL));

        assertSuccess(t, stream_collect(s, NULL, next, finish, &result, NULL));

        //stream_debug(s);

        void *r = stream_run(s, NULL);
        assertNonNull(t, r);

        assertTrueM(t, r == TEST_DATA1[TEST_SIZE - 1], "Wrong value returned");

        logconsole("*** count %d", ctr);
    }

    pass(t);
}
