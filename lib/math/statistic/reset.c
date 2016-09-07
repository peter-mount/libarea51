#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>
#include <area51/math.h>

void statistic_reset_r(struct Statistic *s, struct Statistic *d) {
    if (s && 0 == pthread_mutex_lock(&s->mutex)) {
        if (d) {
            d->value = s->value;
            d->count = s->count;
            d->total = s->total;
            d->min = s->min;
            d->max = s->max;
        }

        s->value = 0;
        s->count = 0;
        s->total = 0;
        s->min = LONG_MAX;
        s->max = LONG_MIN;
        pthread_mutex_unlock(&s->mutex);
    }
}

void statistic_reset(struct Statistic *s) {
    statistic_reset_r(s, NULL);
}