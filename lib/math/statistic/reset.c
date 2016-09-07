#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>
#include <area51/math.h>

void statistic_reset_r(struct Statistic *s, struct Statistic *d, int flag) {
    if (s && 0 == pthread_mutex_lock(&s->mutex)) {
        int f = flag ? flag : STAT_RESET_ALL;

        if (d) {
            d->value = s->value;
            d->count = s->count;
            d->total = s->total;

            if (f & STAT_CALCULATE_MINMAX) {
                if (d->min > s->value)
                    d->min = s->value;
                if (d->max < s->value)
                    d->max = s->value;
            } else {
                d->min = s->min;
                d->max = s->max;
            }
        }

        if (f & STAT_RESET_VALUE)
            s->value = 0;

        if (f & STAT_RESET_COUNT)
            s->count = 0;

        if (f & STAT_RESET_TOTAL)
            s->total = 0;

        if (f & STAT_RESET_MINMAX) {
            s->min = LONG_MAX;
            s->max = LONG_MIN;
        }

        pthread_mutex_unlock(&s->mutex);
    }
}

void statistic_reset(struct Statistic *s) {
    statistic_reset_r(s, NULL, STAT_RESET_ALL);
}