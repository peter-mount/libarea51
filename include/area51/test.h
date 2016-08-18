
#ifndef AREA51_TEST_H
#define AREA51_TEST_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Test Test;

    /*
     * Representation of a suite of tests
     */
    struct TestSuite {
        char *name;
        void (*run)(Test *);
    };

    struct TestResult {
        int run;
        int pass;
        int fail;
    };

    /**
     * Run a suite of tests
     * @param Where to put the results
     * @param Array of TestSuite. Last entry should have null for run
     * @return 
     */
    extern int area51_runTests(struct TestResult *, struct TestSuite *);

    extern void area51_startTest(Test *, const char *);
    extern void area51_passTest(Test *);
    extern void area51_failTest(Test *);

    extern void area51_testResult(Test *, bool, const char *, int, const char *, const char *);
    
#define startTest(t) area51_startTest((t), __PRETTY_FUNCTION__)
#define failM(t,m) return area51_testResult((t),false,__FILE__,__LINE__,__PRETTY_FUNCTION__,(m))
#define fail(t) failM(t,NULL)
#define passM(t,m) return area51_testResult((t),true,__FILE__,__LINE__,__PRETTY_FUNCTION__,(m))
#define pass(t) passM(t,NULL)

#define assertSuccess(t,v) if(v) fail((t))
#define assertSuccessM(t,v,m) if(v) failM((t),(m))
#define assertFailure(t,v) if(!(v)) fail((t))
#define assertFailureM(t,v,m) if(!(v)) failM((t),(m))

#define assertNull(t,v) assertSuccess(t,v)
#define assertNullM(t,v,m) assertSuccessM(t,v,m)
#define assertNonNull(t,v) assertFailure(t,v)
#define assertNonNullM(t,v,m) assertFailureM(t,v,m)
    
#define assertTrue(t,p) assertFailure(t,p)
#define assertTrueM(t,p,m) assertFailureM(t,p,m)
#define assertFalse(t,p) assertSuccess(t,p)
#define assertFalseM(t,p,m) assertSuccessM(t,p,m)
    
#ifdef __cplusplus
}
#endif

#endif /* AREA51_TEST_H */

