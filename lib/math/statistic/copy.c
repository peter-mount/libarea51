#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>
#include <area51/math.h>

void statistic_copy(struct Statistic *d, struct Statistic *s) {
    if (d && s && 0 == pthread_mutex_lock(&s->mutex)) {
        memcpy(d, s, sizeof (struct Statistic));
        memset(&d->mutex, 0, sizeof (pthread_mutex_t));
        pthread_mutex_unlock(&s->mutex);
    }
}