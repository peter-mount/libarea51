
#include "pool_int.h"

void pool_offer(struct Pool *p, void *entry) {
    if (p && entry) {
        int f = 1;

        struct PoolInt *pi = (struct PoolInt *) p;
        pthread_mutex_lock(&pi->mutex);

        int s = list_size(&pi->list);
        if (s < pi->maxSize) {
            struct PoolEntry *e = (struct PoolEntry *) malloc(sizeof (struct PoolEntry));
            if (e) {
                memset(e, 0, sizeof (struct PoolEntry));
                e->entry = entry;
                list_addTail(&pi->list, &e->node);
                f = 0;
            }
        }

        // Get here then free the entry
        if (f) {
            if (pi->free)
                pi->free(entry);
            else
                free(entry);
        }

        pthread_mutex_unlock(&pi->mutex);
    }
}