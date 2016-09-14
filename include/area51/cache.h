/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cache.h
 * Author: peter
 *
 * Created on 10 September 2016, 08:42
 */

#ifndef AREA51_CACHE_H
#define AREA51_CACHE_H

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

    /*
     * A cache of entries that can be expired by age (optional) and least used
     * when the cache is full.
     * 
     */
    typedef struct Cache Cache;

    /**
     * 
     * @param maxSize Max number of entries in the cache
     * @param maxage Max age of entries, 0 not to expire by age
     * @param hash hash function for key
     * @param equals equals function for key
     * @param fk free key
     * @param fv free value
     * @return 
     */
    extern Cache *cacheCreate(size_t maxSize, time_t maxage,
            int (*hash)(void* key), bool (*equals)(void* keyA, void* keyB),
            void (*fk)(void *),
            void (*fv)(void *)
            );
    
    /**
     * Free a cache
     * @param c
     */
    extern void cacheFree(Cache *c);
    /**
     * Get a value from the cache
     * @param c Cache
     * @param k key
     * @return 
     */
    extern void *cacheGet(Cache *c, void *k);

    /**
     * Put an entry into the cache. If v is null then this is a remove instead.
     * @param c Cache
     * @param k key
     * @param v value
     */
    extern void cachePut(Cache *c, void *k, void *v);

    /**
     * Remove an entry from the cache
     * @param c
     * @param k
     */
    extern void cacheRemove(Cache *c, void *k);

    /**
     * Remove all entries from the cache, clearing it
     * @param c Cache
     */
    extern void cacheRemoveAll(Cache *c);
    
    /**
     * Remove entries if they pass a Predicate
     * @param c Cache
     * @param p predicate, returns true to remove, false to keep
     */
    extern void cacheRemoveIf(Cache *c, bool(*p)(void *k, void *v));
    
    /**
     * The size of the cache at a moment in time
     * 
     * @param c
     * @return 
     */
    extern size_t cacheSize(Cache *c);

#ifdef __cplusplus
}
#endif

#endif /* CACHE_H */

