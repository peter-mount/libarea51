#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <area51/thread.h>
#include <area51/threadpool.h>
#include <limits.h>
#include <string.h>

#include "main-int.h"

MainTasks *area51_mainInit() {
    MainTasks *t = malloc(sizeof (struct MainTasks));
    if (t) {
        memset(t, 0, sizeof (struct MainTasks));

        list_init(&t->tasks);

        pthread_mutex_init(&t->mutex, NULL);

        t->period = DEFAULT_PERIOD;
        t->threadPoolSize = DEFAULT_POOL_SIZE;
    }
    return t;
}

void area51_mainSetVerbosity(MainTasks *t, int s) {
    if (t) {
        area51_mainLock(t);
        t->verbose = s < 0 ? 0 : s > 3 ? 3 : s;
        area51_mainUnlock(t);
    }
}

void area51_mainSetThreadPoolSize(MainTasks *t, int s) {
    if (t) {
        area51_mainLock(t);
        if (!t->initialised) {
            t->threadPoolSize = s < 1 ? DEFAULT_POOL_SIZE : s > 255 ? 255 : s;
        }
        area51_mainUnlock(t);
    }
}

void area51_mainSetPeriod(MainTasks *t, int s) {
    if (t) {
        area51_mainLock(t);
        // So we don't run continuously, period is in 5 second steps
        int p = 5 * (s / 5);
        t->period = p < 1 || p > DEFAULT_PERIOD ? DEFAULT_PERIOD : p;
        area51_mainUnlock(t);
    }
}
