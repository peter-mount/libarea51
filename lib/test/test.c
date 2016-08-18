#include <stdio.h>
#include <stdlib.h>
#include <area51/log.h>
#include <area51/test.h>
#include <string.h>

static const char *SEP = "======================================================================";

struct Test {
    struct TestResult r;
};

static void summarise(struct TestResult *r) {
    logconsole(SEP);
    logconsole("Test results: Run %d Passed %d Failed %d", r->run, r->pass, r->fail);
}

void area51_startTest(Test *t, const char *title) {
    t->r.run++;
    logconsole(SEP);
    logconsole("Beginning test %d - %s", t->r.run, title);
}

void area51_testResult(Test *t, bool s, const char *f, int l, const char *m, const char *msg) {
    if (s) {
        t->r.pass++;
        logconsole("Test %s passed", m);
    } else {
        t->r.fail++;
        logconsole("Test %s failed (%s:%d)", m, f, l);
    }
    if(msg)
        logconsole(msg);
}

int area51_runTests(struct TestResult *total, struct TestSuite *tests) {
    memset(total, 0, sizeof (struct TestResult));

    for (struct TestSuite *test = tests; test && test->name; test++) {
        Test current;
        memset(&current, 0, sizeof (Test));

        logconsole(SEP);
        logconsole("Beginning %s tests", test->name);

        test->run(&current);

        summarise(&current.r);
        total->run += current.r.run;
        total->pass += current.r.pass;
        total->fail += current.r.fail;
    }

    logconsole(SEP);
    logconsole("");
    summarise(total);
    logconsole(SEP);

    return total->fail ? EXIT_FAILURE : EXIT_SUCCESS;
}

