#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
#include <area51/thread.h>
#include <area51/threadpool.h>
#include <area51/log.h>
#include <unistd.h>

#include "main-int.h"

/**
 * Thread pool worker, run a task
 * @param n Node whos value points to the MainTask
 * @param c MainTasks
 * @return 
 */
static void *worker(Node *n, void *c) {
    if (n) {
        MainTask *task = n->value;
        free(n);

        if (task->prior)
            task->prior(task);

        if (task->task)
            task->task(task);

        if (task->after)
            task->after(task);
    }
}

/**
 * Submit a task to the worker pool
 */
static void submit(MainTasks *tasks, MainTask *task) {
    Node *job = malloc(sizeof (Node));
    if (job) {
        job->value = task;
        threadpool_submit(&tasks->threadPool, job);
    }
}

void area51_mainLoop(MainTasks *tasks) {
    if (!tasks)
        return;

    area51_mainLock(tasks);

    // Do nothing if we are running already
    if (tasks->running) {
        area51_mainUnlock(tasks);
        return;
    }

    if (!tasks->initialised) {
        // Final initialisation, the thread pool
        threadpool_init(&tasks->threadPool, tasks->threadPoolSize);
        threadpool_start(&tasks->threadPool, worker, NULL);

        tasks->initialised = 1;
    }

    // The main loop
    tasks->running = true;
    while (tasks->running) {

        // Sleep outside the lock, sanitising the period before hand
        int period = tasks->period;
        if (tasks->verbose)
            logconsole("Sleeping %ds", period);
        area51_mainUnlock(tasks);
        sleep(period);
        area51_mainLock(tasks);

        if (tasks->verbose)
            logconsole("Waking up");

        time_t now;
        time(&now);

        Node *n = list_getHead(&tasks->tasks);
        while (list_isNode(n)) {
            MainTask *task = (MainTask *) n;

            if (task->next < now)
                submit(tasks, task);

            n = list_getNext(n);
        }
    }

    // No longer running so release the lock
    area51_mainUnlock(tasks);
}
