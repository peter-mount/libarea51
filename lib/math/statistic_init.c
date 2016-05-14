#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <area51/math.h>

void statistic_init(struct Statistic *s) {
    if (s) {
        pthread_mutex_init(&s->mutex, NULL);
        statistic_reset(s);
    }
}