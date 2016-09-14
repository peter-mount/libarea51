#include "tests.h"

extern void test_stream(Test *);
extern void test_id(Test *);
extern void test_cache(Test *);
extern void test_hashmap(Test *);

static struct TestSuite TESTS [] = {
    {"Stream", test_stream},
  //  {"Hashmap", test_hashmap},
  //  {"ID Generators", test_id},
    {"Cache", test_cache},
    // End test marker
    {NULL, NULL}
};

int main(int argc, char** argv) {
    struct TestResult result;
    return area51_runTests(&result, TESTS);
}
