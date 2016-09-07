#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <area51/math.h>

void statistic_increment(struct Statistic *s) {
    if (s && 0 == pthread_mutex_lock(&s->mutex)) {
        long v = ++s->value;
        s->count++;
        s->total++;
        if (v < s->min)s->min = v;
        if (v > s->max)s->max = v;
        pthread_mutex_unlock(&s->mutex);
    }
}