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
    extern void statistic_reset_r(struct Statistic *, struct Statistic *);
    extern void statistic_setValue(struct Statistic *, long v);
    extern void statistic_recorder(MainTasks *, struct Statistic *, struct json_object *);

#ifdef __cplusplus
}
#endif

#endif /* AREA51_MATH_H */

