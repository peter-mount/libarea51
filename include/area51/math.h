/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   math.h
 * Author: peter
 *
 * Created on 13 May 2016, 19:47
 */

#ifndef AREA51_MATH_H
#define AREA51_MATH_H

#include <pthread.h>
#include <area51/json.h>
#include <area51/main.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct Statistic {
        long value;
        long count;
        long min;
        long max;
        long total;
        pthread_mutex_t mutex;
    };

    extern void statistic_copy(struct Statistic *, struct Statistic *);
    extern long statistic_getValue(struct Statistic *);
    extern long statistic_getCount(struct Statistic *);
    extern long statistic_getMin(struct Statistic *);
    extern long statistic_getMax(struct Statistic *);
    extern long statistic_getTotal(struct Statistic *);
    extern void statistic_init(struct Statistic *);
    extern void statistic_increment(struct Statistic *);
    extern void statistic_reset(struct Statistic *);
    extern void statistic_setValue(struct Statistic *, long v);

#define STAT_RESET_NONE   0x00
    // Reset just the value
#define STAT_RESET_VALUE  0x01
    // Reset the count
#define STAT_RESET_COUNT  0x02
    // Reset the total
#define STAT_RESET_TOTAL  0x04
    // Reset the min/max values
#define STAT_RESET_MINMAX 0x08
    // Reset all values
#define STAT_RESET_ALL    0xff
    // Don't copy min/max but update it instead
#define STAT_CALCULATE_MINMAX 0x100

    /**
     * Reset a statistic
     * @param Statistic to reset
     * @param if not null, statistic to copy into
     * @param flags on what to reset
     */
    extern void statistic_reset_r(struct Statistic *, struct Statistic *, int);

    /**
     * Add a MainTask to reset a statistic and perform standard options in logging it.
     * 
     * The supplied json object should have:
     * "name"     The name of the statistic in logging
     * "log"      true to log to the console
     * "period    the period in seconds to sample. Default is 60
     * "reset     default "all", defines what to reset each time, one of: "none", "all", "minmax", "value"
     * "minmax    true to update min/max in recorded value rather than that of the source statistic
     * "http.get" Array of url's to submit an http get request
     * 
     * For "http.get" you can use the following substitutions: for each statistic value:
     * "{count}", "{max}", "{min}", "{total}", "{value}"
     * 
     * Example:
     * {
     *   "name": "TD message rate",
     *   "log": true,
     *   "period": 60,
     *   "minmax": true,
     *   "http.get": [
     *     "http://example.com/update?api_key=123456&field1={count}&field2={min}&field3={max}"
     *   ]
     * }
     * 
     * @param MainTasks
     * @param statistic
     * @param json configuration
     */
    extern void statistic_recorder(MainTasks *, struct Statistic *, struct json_object *);

#ifdef __cplusplus
}
#endif

#endif /* AREA51_MATH_H */

