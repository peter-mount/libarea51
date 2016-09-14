/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cache-int.h
 * Author: peter
 *
 * Created on 10 September 2016, 08:43
 */

#ifndef CACHE_INT_H
#define CACHE_INT_H

#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <area51/cache.h>
#include <area51/hashmap.h>
#include <area51/list.h>

#include "../memory/freeable-int.h"
#ifdef __cplusplus
extern "C" {
#endif

    struct Cache {
        // List of entries by key
        Hashmap *map;
        // List of entries ordered by access
        List list;
        pthread_mutex_t mutex;
        // Max age for an entry
        time_t maxage;
        // If we have this number of entries then remove the oldest
        size_t maxSize;
        // method to free a key
        void (*freeKey)(void *);
        // Lookup function to use when we get a non-existent entry
        void (*lookup) (void *, void *, Freeable *);
        Freeable lookupContext;
        // Flags
        unsigned int updateTime : 1;
        unsigned int expireLeastUsed : 1;
        unsigned int expireOriginalTime : 1;
        unsigned int noUpdateIfSameValue : 1;
        unsigned int lookupConcurrent : 1;
    };

    struct CacheEntry {
        Node node;
        // key
        void *key;
        // Value
        Freeable value;
        // Expiry time
        time_t expires;
        // The original expiry time
        time_t original_expires;
        // Mutex for CACHE_LOOKUP_CONCURRENT mode
        pthread_mutex_t mutex;
    };

    extern void cacheLock(Cache *);
    extern void cacheUnlock(Cache *);
    extern struct CacheEntry *cacheGetEntry(Cache *, void *);
    extern struct CacheEntry *cachePutEntry(Cache *, void *);
    extern void cacheRemoveEntry(Cache *, struct CacheEntry *);
    extern void cacheExpireIntl(Cache *);

#ifdef __cplusplus
}
#endif

#endif /* CACHE_INT_H */

