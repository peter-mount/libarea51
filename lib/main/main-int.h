#ifndef MAIN_INT_H
#define MAIN_INT_H

#include <pthread.h>
#include <time.h>
#include <area51/list.h>
#include <area51/main.h>
#include <area51/memory.h>
#include <area51/thread.h>
#include <area51/threadpool.h>

#ifdef __cplusplus
extern "C" {
#endif
    // Default loop period is 60
#define DEFAULT_PERIOD 60

#define DEFAULT_POOL_SIZE 10

    struct MainTasks {
        // List of tasks to run
        List tasks;

        // Mutex
        pthread_mutex_t mutex;

        // Worker thread pool
        struct thread_pool threadPool;

        // thread pool size, min 1 max 255, default DEFAULT_POOL_SIZE
        unsigned int threadPoolSize : 8;

        // Sleep period in seconds
        unsigned int period : 8;

        // Verbosity, 0=none, 1=debug, 2,3 finer detail
        unsigned int verbose : 2;

        // Always 1, if we ever want to shutdown then set to 0
        unsigned int running : 1;
        
        // Once set we have initialised
        unsigned int initialised : 1;
    };

    struct MainTask {
        // Entry in task list
        Node node;
        // Link to parent MainTasks
        MainTasks *tasks;

        // When to run this task
        time_t next;

        // Called prior to the task
        void (*prior)(MainTask *);

        // Called after the task
        void (*after)(MainTask *);

        // Task to run
        void (*task)(MainTask *);

        // userdata for task
        Freeable *userdata;

        // Task specific data

        union {
            // TASK_PERIODIC period
            unsigned int period;
        };
    };

    extern void area51_mainLock(MainTasks *);
    extern void area51_mainUnlock(MainTasks *);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_INT_H */

