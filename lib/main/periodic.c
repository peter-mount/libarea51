#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <area51/thread.h>
#include <area51/threadpool.h>
#include <limits.h>
#include <string.h>

#include "main-int.h"

static void after(MainTask *task) {
    area51_mainLock(task->tasks);

    // Move to next period
    task->next += task->period;

    // If in the past then move forward in time - i.e. we overran
    time_t now;
    time(&now);
    if (task->next < now)
        task->next = now + task->period;

    area51_mainUnlock(task->tasks);
}

int area51_mainRunPeriodic(MainTasks *tasks, void (*task)(MainTask *), unsigned int period, void *c, void (*f)(void *)) {
    if (tasks && task && period > 0) {

        MainTask *t = area51_mainNewTask(task, c, f);
        if (t) {
            t->after = after;

            // The period & initial offset
            t->period = period<1?DEFAULT_PERIOD:period;
            
            time(&t->next);
            t->next += period;
            
            area51_mainAdd(tasks, t);
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}
