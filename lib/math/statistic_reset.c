#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <area51/math.h>

void statistic_reset(struct Statistic *s) {
    if (s && 0 == pthread_mutex_lock(&s->mutex)) {
        s->value = 0;
        s->count = 0;
        s->total = 0;
        s->min = LONG_MAX;
        s->max = LONG_MIN;
        pthread_mutex_unlock(&s->mutex);
    }
}