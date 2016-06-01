
#include "pool_int.h"

void pool_fill(struct Pool *p) {
    if (p) {

        struct PoolInt *pi = (struct PoolInt *) p;
        pthread_mutex_lock(&pi->mutex);

        while (list_size(&pi->list) < pi->maxSize) {
            struct PoolEntry *e = (struct PoolEntry *) malloc(sizeof (struct PoolEntry));
            if (e) {
                memset(e, 0, sizeof (struct PoolEntry));
                e->entry = pi->create();
                if (e->entry)
                    list_addTail(&pi->list, &e->node);
                else {
                    // Bail out as we failed to create an object
                    free(e);
                    pthread_mutex_unlock(&pi->mutex);
                    return;
                }
            }
        }

        pthread_mutex_unlock(&pi->mutex);
    }
}
