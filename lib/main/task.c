#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <area51/thread.h>
#include <area51/threadpool.h>
#include <limits.h>
#include <string.h>

#include "main-int.h"

void area51_mainAdd(MainTasks *tasks, MainTask *t) {
    if (tasks && t && !t->tasks) {
        area51_mainLock(tasks);

        t->tasks = tasks;
        list_addTail(&tasks->tasks, (Node *) t);

        area51_mainUnlock(tasks);
    }
}

void area51_mainFreeTask(MainTask *task) {
    if (!task)
        return;

    if (task->tasks) {
        area51_mainLock(task->tasks);
        list_remove(&task->node);
        area51_mainUnlock(task->tasks);
    }

    freeable_free(task->userdata);
    free(task);
}

MainTask *area51_mainNewTask(void (*task)(MainTask *), void *c, void (*f)(void *)) {
    MainTask *t = malloc(sizeof (struct MainTask));
    if (t) {
        memset(t, 0, sizeof (struct MainTask));

        t->task = task;

        // Default post action is to free the task
        t->after = area51_mainFreeTask;

        // No point creating one if present
        if (c)
            t->userdata = freeable_new(c, f);
    }
    return t;
}

void *area51_mainGetUserData(MainTask *t) {
    return t ? freeable_get(t->userdata) : NULL;
}

void area51_mainSetUserData(MainTask *t, void *c, void (*f)(void *)) {
    t->userdata = freeable_set(t->userdata, c, f);
}

MainTasks *area51_mainGetMainTasks(MainTask *t) {
    return t ? t->tasks : NULL;
}
