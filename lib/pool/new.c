
#include "pool_int.h"

struct Pool *pool_new(int maxSize, void *(*create) (), void (*free) (void *)) {
    struct PoolInt *p = (struct PoolInt *) malloc(sizeof (struct PoolInt));
    if (p) {
        memset(p, 0, sizeof (struct PoolInt));
        list_init(&p->list);
        pthread_mutex_init(&p->mutex, NULL);
        p->maxSize = maxSize < 1 ? 1 : maxSize;
        p->create = create;
        p->free = free;
    }
    return &p->pool;
}