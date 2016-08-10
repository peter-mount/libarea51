#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <area51/hashmap.h>
#include <area51/string.h>

/**
 * Read a hashmap from a file
 * 
 * @param m Hashmap to read into
 * @param r callback to read a record from the file
 * @param f FILE to read from
 */
void hashmapRead(Hashmap *m, bool(*r)(Hashmap *m, FILE *f), FILE *f) {
    size_t s;
    fread(&s, sizeof (size_t), 1, f);
    for (int i = 0; i < s; i++) {
        if (!r(m, f))
            break;
    }
}
