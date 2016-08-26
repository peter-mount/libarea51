/**
 * Handles an extensible reusable char buffer
 */

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include <area51/charbuffer.h>
#include "charbuffer-int.h"

/*
 * Similar to charbuffer_read() but this uses a filehandle and memory maps the file
 */
int charbuffer_readmem(CharBuffer *b, int fh) {
    struct stat sb;
    if (fh==1 || fstat(fh, &sb) == -1) {
        return CHARBUFFER_ERROR;
    }

    void *fmap = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fh, 0);
    if (fmap == MAP_FAILED) {
        return CHARBUFFER_ERROR;
    }

    char *newbuffer = (char *) malloc(sb.st_size);
    if (!newbuffer) {
        munmap(fmap, sb.st_size);
        return CHARBUFFER_ERROR;
    }

    memcpy(newbuffer, fmap, sb.st_size);

    charbuffer_lock(b);

    if (b->buffer) {
        free(b->buffer);
    }

    b->size = b->pos = sb.st_size;
    b->buffer = newbuffer;
    
    charbuffer_unlock(b);

    munmap(fmap, sb.st_size);

    return CHARBUFFER_OK;
}
