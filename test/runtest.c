#include "tests.h"

extern void test_stream(Test *);

static struct TestSuite TESTS [] = {
    {"Stream", test_stream},
    // End test marker
    {NULL, NULL}
};

int main(int argc, char** argv) {
    struct TestResult result;
    return area51_runTests(&result, TESTS);
}
