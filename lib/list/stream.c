
#include <stdio.h>
#include <stdlib.h>
#include <area51/list.h>
#include <area51/stream.h>

static void supplier(StreamData *d) {
    Node *n = stream_getTaskContext(d);
    if (n && list_isNode(n)) {
        // The node is the value to pass on
        stream_setVal(d, n, NULL);

        // Move to the next node
        stream_setTaskContext(d, list_getNext(n), NULL);

        // Pass the value down the stream
        stream_next(d);
    } else
        stream_terminate(d);
}

Stream *list_stream(List *l) {
    Stream *s = stream_new();
    if (s && l)
        stream_invoke(s, supplier, list_getHead(l), NULL);
    return s;
}
