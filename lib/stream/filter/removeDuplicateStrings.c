/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <area51/stream.h>

struct ctx {
    bool first;
    char *last;
};

static void removeDuplicate(StreamData *d) {
    struct ctx *c = stream_getTaskContext(d);
    if (c) {
        char *v = stream_getVal(d);
        if (c->first || (v != c->last && strcmp(v, c->last))) {

            c->first = false;
            c->last = v;
            stream_next(d);
        }
    }
}

/*
 * Remove any duplicate strings.
 */
int stream_removeDuplicateStrings(Stream *s) {
    struct ctx *c = malloc(sizeof (struct ctx));
    if (c) {
        c->first = true;
        if (!stream_invoke(s, removeDuplicate, c, free))
            return EXIT_SUCCESS;
        free(c);
    }
    return EXIT_FAILURE;
}
