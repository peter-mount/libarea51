
#include "pool_int.h"

void pool_free(struct Pool *p) {
    if (p) {
        struct PoolInt *pi = (struct PoolInt *) p;
        Node *n = list_removeHead(&pi->list);
        while (n) {
            struct PoolEntry *e = (struct PoolEntry *) n;
            if (pi->free && e->entry)
                pi->free(e->entry);
            else
                free(e->entry);
            free(e);
            n = list_removeHead(&pi->list);
        }
        free(p);
    }
}