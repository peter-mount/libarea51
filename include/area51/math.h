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

    extern long statistic_getValue(struct Statistic *s);
    extern long statistic_getCount(struct Statistic *s);
    extern long statistic_getMin(struct Statistic *s);
    extern long statistic_getMax(struct Statistic *s);
    extern long statistic_getTotal(struct Statistic *s);
    extern void statistic_init(struct Statistic *s);
    extern void statistic_reset(struct Statistic *s);
    extern void statistic_setValue(struct Statistic *s, long v);

#ifdef __cplusplus
}
#endif

#endif /* AREA51_MATH_H */

