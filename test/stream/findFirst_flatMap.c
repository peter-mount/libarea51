/*
 * Test that findFirst works correctly when being supplied by a substream
 * 
 */
#include "../tests.h"
#include <area51/list.h>
#include <area51/stream.h>

#define TEST_SIZE 5

static struct List *list = NULL;

static char *TEST_DATA[] = {"a", "b", "c", "d", "e"};

static char *TEST_DATA1[] = {"f", "g", "h", "i", "j"};

static void next(void *c, void *v) {
    void **p = c;
    *p = v;
}

static void *finish(void *c) {
    void **p = c;
    return *p;
}

static Stream *flatMap(StreamData *d, void *c) {
    Stream *s = list_stream(list);
    list_map_node_name(s);
    return s;
}

void test_stream_findFirst_flatMap(Test *t) {
    void *result = NULL;

    startTest(t);

    list = malloc(sizeof (List));
    list_init(list);
    for (int i = 0; i < TEST_SIZE; i++)
        list_addTail(list, node_alloc(TEST_DATA1[i]));

    Stream *s = stream_array((void**) TEST_DATA, TEST_SIZE);
    assertNonNull(t, s);

    assertSuccess(t, stream_flatMap(s, flatMap, NULL));

    assertSuccess(t, stream_findFirst(s));

    assertSuccess(t, stream_collect(s, NULL, next, finish, &result, NULL));

    //stream_debug(s);

    void *r = stream_run(s, NULL);
    assertNonNull(t, r);

    // We should get the first entry in the second data set
    assertTrueM(t, r == TEST_DATA1[0], "Wrong value returned");

    pass(t);
}
