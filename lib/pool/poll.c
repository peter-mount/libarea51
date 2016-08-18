
#include "pool_int.h"

void *pool_poll(struct Pool *p) {
    void *entry = NULL;
    if (p) {
        struct PoolInt *pi = (struct PoolInt *) p;
        pthread_mutex_lock(&pi->mutex);

        Node *n = list_removeHead(&pi->list);
        if (n) {
            struct PoolEntry *e = (struct PoolEntry *) n;
            entry = e->entry;
            free(e);
        }

        pthread_mutex_unlock(&pi->mutex);

        if (!entry && pi->create)
            entry = pi->create();
    }
    return entry;
}