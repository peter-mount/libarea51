/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   filelogger-int.h
 * Author: peter
 *
 * Created on 07 September 2016, 19:29
 */

#ifndef FILELOGGER_INT_H
#define FILELOGGER_INT_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <area51/charbuffer.h>
#include <area51/filelogger.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct FileLogger {
        pthread_mutex_t mutex;
        // Directory path to where to store data
        char *directory;
        // Prefix to file name 
        char *prefix;
        // Suffix to file name
        char *suffix;
        // Workspace
        CharBuffer *b;
        // Current file
        FILE *f;
        char *path;
        //
        time_t time;
        struct tm tm;
        // The last minute/hour/day value, if this differs in tm then we rotate
        int last;
        // Rotation option
        int rotate;
    };


    extern void filelogger_rotate(FileLogger *);
    extern void filelogger_lock(FileLogger *);
    extern void filelogger_unlock(FileLogger *);
    
#ifdef __cplusplus
}
#endif

#endif /* FILELOGGER_INT_H */

