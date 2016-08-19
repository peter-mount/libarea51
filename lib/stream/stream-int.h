/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stream.h
 * Author: peter
 *
 * Created on 17 August 2016, 10:13
 */

#ifndef AREA51_STREAM_INT_H
#define AREA51_STREAM_INT_H

#include <area51/stream.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct Stream {
        // The first task
        StreamTask *start;

        // The last task
        StreamTask *tail;

        // User Context data for the stream 
        void *context;

        // If set function to call to free context
        void (*freeContext)(void *);

        // If set to false the source should stop feeding data
        bool continueStream;

        // Result of any reduction
        void *result;

        bool debug;
        int sid;
    };

    struct StreamTask {
        // Link to the next task
        StreamTask *next;

        // Link to the owning Stream
        Stream *stream;

        // The action for this task
        void (*action)(StreamData *);

        // Context for this task
        void *taskContext;

        // If set function to free taskContext
        void (*freeTaskContext)(void *);

        // Used in debugging
        unsigned int tid : 8;
        const char *fname;
        const char *sym;
    };

    struct StreamData {
        StreamTask *task;
        void *val;
        void (*free)(void *);
    };

    struct StreamCollector {
        Stream *stream;
        void (*init)(void *);
        void (*next)(void *, void*);
        void *(*finish)(void *);
        bool initRequired;
        void *context;
        void (*freeContext)(void *);
    };

    extern void stream_debug_r(Stream *, bool);
    extern void stream_debug_task(StreamData *);
    extern void stream_debug_res(const char *, void *);
    extern void stream_debug_run(const char *, void *, void *);

#ifdef __cplusplus
}
#endif

#endif /* AREA51_STREAM_INT_H */
