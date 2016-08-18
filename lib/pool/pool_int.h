/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pool.h
 * Author: peter
 *
 * Created on 01 June 2016, 19:36
 */

#ifndef AREA51_POOL_INT_H
#define AREA51_POOL_INT_H

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <area51/list.h>
#include <area51/pool.h>

#ifdef __cplusplus
extern "C" {
#endif

    // A thread safe object pool

    struct PoolInt {
        struct Pool pool;
        List list;
        // Max pool size
        int maxSize;
        pthread_mutex_t mutex;
        // Create an entry
        void *(*create) ();
        // Free an entry
        void (*free) (void *);
    };

    struct PoolEntry {
        Node node;
        void *entry;
    };

    /**
     * Create a pool. Once created you need to set the create and free hooks for it to be useful.
     *
     * If pool->create is null then polling an empty pool will return null.
     * 
     * if pool->free is null then free(entry) will be called if the pool is full when offered.
     * 
     * @param maxSize Max size of spare entries in the pool
     * @return 
     */
    extern struct Pool *pool_new(int maxSize, void *(*create) (), void (*free) (void *));
    /**
     * Free a pool. All entries will be removed and freed.
     * 
     * When freeing then the pool->free method will be used unless null then free() will be used instead.
     * @param p Pool
     */
    extern void pool_free(struct Pool *p);
    /**
     * Poll for a new entry from the pool
     * @param p Pool
     * @return entry or null if unable to create one
     */
    extern void *pool_poll(struct Pool *p);
    /**
     * Offer an entry to the pool
     * @param p Pool
     * @param e Entry
     */
    extern void pool_offer(struct Pool *p, void *e);


#ifdef __cplusplus
}
#endif

#endif /* AREA51_POOL_INT_H */

