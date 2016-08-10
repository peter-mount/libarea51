#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <area51/hashmap.h>
#include <area51/string.h>

/**
 * Write the contents of a hashmap to a file.
 * 
 * The callback will be called with 3 parameters, the key, the value and the
 * context which happens to be the supplied FILE.
 * 
 * The written data will be a size_t entry containing the number of entries in
 * the map, followed by that number of records.
 * 
 * @param m Hashmap to write
 * @param w callback to handle the write
 * @param f FILE to write to.
 */
void hashmapWrite(Hashmap *m, bool(*w)(void *k, void *v, void *c), FILE *f) {
    size_t s = hashmapSize(m);
    fwrite(&s, sizeof (size_t), 1, f);
    hashmapForEach(m, w, f);
}
