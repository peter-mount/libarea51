#include <stdlib.h>
#include <area51/list.h>
#include <area51/stream.h>

Stream *list_flatMap(void *v, void *c) {
    return list_stream((List *) v);
}
