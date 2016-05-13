#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <area51/math.h>

long statistic_getMax(struct Statistic *s) {
    long v = 0;
    if (s && 0 == pthread_mutex_lock(&s->mutex)) {
        v = s->max;
        pthread_mutex_unlock(&s->mutex);
    }
    return v;
}