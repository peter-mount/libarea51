
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

void *stream_free(Stream *s) {
    void *r=NULL;
    
    if (s) {
        r = s->result;
        
        StreamTask *t = s->start;
        while (t) {
            StreamTask *n = t->next;
            if (t->taskContext && t->freeTaskContext)
                t->freeTaskContext(t->taskContext);
            free(t);
            t = n;
        }

        if (s->context && s->freeContext)
            s->freeContext(s->context);

        free(s);
    }
    
    return r;
}
