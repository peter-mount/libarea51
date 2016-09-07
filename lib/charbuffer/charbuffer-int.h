/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   charbuffer-int.h
 * Author: peter
 *
 * Created on 26 August 2016, 12:45
 */

#ifndef CHARBUFFER_INT_H
#define CHARBUFFER_INT_H

#ifdef __cplusplus
extern "C" {
#endif

    // Initial charbuffer size
#define CHARBUFFER_INITIAL_SIZE 1024

    struct charbuffer {
        // The current position in the buffer where new data will be appended
        int pos;
        // The actual size of the buffer in memory, not it's contents
        size_t size;
        // The actual memory being used by the buffer
        char *buffer;
        // mutex used to ensure the buffer is concurrent
        pthread_mutex_t mutex;
    };

    extern int charbuffer_ensure_capacity(CharBuffer *, int);
    extern void charbuffer_lock(CharBuffer *);
    extern void charbuffer_unlock(CharBuffer *);

#ifdef __cplusplus
}
#endif

#endif /* CHARBUFFER_INT_H */

