#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <area51/thread.h>
#include <area51/threadpool.h>
#include <limits.h>

#include "main-int.h"

void area51_mainLock(MainTasks *tasks) {
    if (tasks)
        pthread_mutex_lock(&tasks->mutex);
}

void area51_mainUnlock(MainTasks *tasks) {
    if (tasks)
        pthread_mutex_unlock(&tasks->mutex);
}
