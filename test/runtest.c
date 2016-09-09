#include "tests.h"

extern void test_stream(Test *);
extern void test_id(Test *);

static struct TestSuite TESTS [] = {
    {"Stream", test_stream},
    {"ID Generators", test_id},
    // End test marker
    {NULL, NULL}
};

int main(int argc, char** argv) {
    struct TestResult result;
    return area51_runTests(&result, TESTS);
}
