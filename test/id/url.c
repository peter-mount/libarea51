/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include <area51/hashmap.h>
#include <area51/id.h>

void test_id_url(Test *t) {

    Hashmap *m = hashmapCreate(100, hashmapStringHash, hashmapStringEquals);

    URLIDGenerator *g = urlidgenerator_new(0, 0, 62, 10);

    for (int i = 0; i < 500; i++) {
        char s[128];
        urlidgenerator_generate(g, s, 120);

        assertTrueM(t, s[0] != 0, "No id generated");
        logconsole("%s", s);

        char *k = strdup(s);
        assertNonNull(t, k);

        void *e = hashmapPut(m, k, k);
        assertNullM(t, e, e);
    }

    pass(t);
}
