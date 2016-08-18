
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream-int.h"

void *stream_free(Stream *s) {
    void *r=NULL;
    
    if (s) {
        
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
        
        r = s->result;

        free(s);
    }
    
    return r;
}
