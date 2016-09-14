/*
 * Test that a basic collector works. Here we will do a basic reduction, keeping
 * the last value received
 * 
 */
#include "../tests.h"
#include <area51/hashmap.h>
#include <area51/id.h>
#include <string.h>

void test_id_url(Test *t) {

    Hashmap *m = hashmapCreate(100, hashmapStringHash, hashmapStringEquals);
    assertNonNull(t, m);

    URLIDGenerator *g = urlidgenerator_new(0, 0, 62, 0);
    assertNonNull(t, g);

    for (int i = 0; i < 50; i++) {
        char s[128];
        urlidgenerator_generate(g, s, 120);

        assertTrueM(t, s[0] != 0, "No id generated");
        //logconsole("%s", s);

        char *k = strdup(s);
        assertNonNull(t, k);

        void *e = hashmapPut(m, k, k);
        assertNullM(t, e, e);
    }

    pass(t);
}
