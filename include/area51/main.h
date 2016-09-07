
#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct MainTasks MainTasks;
    typedef struct MainTask MainTask;

    /**
     * Initialise MainTasks
     * @return MainTasks for null
     */
    extern MainTasks *area51_mainInit();
    /**
     * Set verbosity
     * @param 
     * @param 
     */
    extern void area51_mainSetVerbosity(MainTasks *, int);
    /**
     * Set the main loop sleep period
     * 
     * @param MainTasks
     * @param Period in seconds. 0 For default
     */
    extern void area51_mainSetPeriod(MainTasks *, int);

    /**
     * Set the thread pool size
     * @param MainTasks
     * @param Pool size, 0 for default
     */
    extern void area51_mainSetThreadPoolSize(MainTasks *, int);

    /**
     * Remove a task.
     * 
     * @param MainTasks
     * @param MainTask to remove
     */
    extern void area51_mainRemove(MainTasks *, MainTask *);

    /**
     * Run the MainTasks. This method may never return
     * @param MainTasks
     */
    extern void area51_mainLoop(MainTasks *);

    /**
     * Periodically run a task
     * @param MainTasks
     * @param  task to run
     * @param period in seconds to run
     * @param optional user data
     * @param optional method to free user data
     * @return EXIT_SUCCESS if scheduled, EXIT_FAILURE if not
     */
    extern int area51_mainRunPeriodic(MainTasks *, void (*)(MainTask *), unsigned int, void *, void (*)(void *));

    /**
     * Get UserData for a task
     * @param MainTask
     * @return data or NULL
     */
    extern void *area51_mainGetUserData(MainTask *);
    /**
     * Set userdata for a task
     * @param MainTask
     * @param user data or NULL
     * @param method to free data if not null
     */
    extern void *rea51_mainSetUserData(MainTask *, void *, void (*)(void *));
    /**
     * Return the MainTasks a MainTask is running within
     * @param MainTask
     * @return MainTasks, null if not added
     */
    extern MainTasks *area51_mainGetMainTasks(MainTask *);

    /**
     * Create a new task
     * @param task
     * @param user data
     * @param method to free userdata or NULL
     * @return MainTask or NULL
     */
    extern MainTask *area51_mainNewTask(void (*)(MainTask *), void *, void (*)(void *));
    /**
     * Add a MainTask to a MainTasks
     * @param MainTasks
     * @param MainTask
     */
    extern void area51_mainAdd(MainTasks *, MainTask *);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */

