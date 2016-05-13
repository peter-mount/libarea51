/**
 * Handles an extensible reusable char buffer
 */

#include <string.h>
#include "area51/charbuffer.h"

int charbuffer_append(struct charbuffer *b, char *src) {
    return charbuffer_put(b, src, strlen(src));
}
