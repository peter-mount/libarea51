#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "area51/charbuffer.h"

static char *END = "}\n";
#define END_SIZE 2

/**
 * Terminates the json content in a charbuffer
 * 
 * @param b charbuffer
 */
void charbuffer_end_json(CharBuffer *b) {
    charbuffer_put(b, END, END_SIZE);
}
