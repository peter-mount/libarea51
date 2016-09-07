#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <area51/math.h>

void statistic_setValue(struct Statistic *s, long v) {
    if (s && 0 == pthread_mutex_lock(&s->mutex)) {
        s->value = v;
        s->count++;
        s->total += v;
        if (v < s->min)s->min = v;
        if (v > s->max)s->max = v;
        pthread_mutex_unlock(&s->mutex);
    }
}