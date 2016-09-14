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
#include <area51/memory.h>

#ifdef __cplusplus
extern "C" {
#endif

    /*
     * A cache of entries that can be expired by age (optional) and least used
     * when the cache is full.
     * 
     */
    typedef struct Cache Cache;

    /*
     *  If set, a get will update the entry timestamp so we don't expire it
     */
#define CACHE_GET_UPDATE_TIME       0x01
    /*
     *  If set then a get moves the entry so when we are full we remove the
     * least used enty rather than the oldest
     */
#define CACHE_EXPIRE_LEAST_USED     0x02
    /*
     * If set then when the cache is expired we expire entries based on when
     * the value was set rather than when they were last used.
     * 
     * This only kicks in when cacheExpire() is used or when the auto-expiry
     * thread is used.
     */
#define CACHE_EXPIRE_ORIGINAL_TIME  0x04
    /*
     * If set then when a put is made with the same value as already in the
     * cache then we do nothing to the existing entry, no time updates etc
     */
#define CACHE_NO_UPDATE_IF_VALUE_SAME  0x08
    /*
     * If set and we have a lookup function then only the cache key is locked
     * until the lookup finishes
     */
#define CACHE_LOOKUP_CONCURRENT 0x10

    /**
     * 
     * @param maxSize Max number of entries in the cache
     * @param maxage Max age of entries, 0 not to expire by age
     * @param hash hash function for key
     * @param equals equals function for key
     * @param fk free key
     * @param lookup optional lookup function when get misses
     * @param lookupContext optional context
     * @param lookupFree free lookupContext
     * @return 
     */
    extern Cache *cacheCreate(size_t maxSize, time_t maxage,
            int (*hash)(void* key), bool (*equals)(void* keyA, void* keyB),
            void (*fk)(void *),
            unsigned int flags,
            void (*lookup)(void *, void *, Freeable *),
            void *lookupContext,
            void (*lookupFree)(void *)
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
    extern void cachePut(Cache *c, void *k, void *v, void (*f)(void *));

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
     * @param c Cache
     * @return 
     */
    extern size_t cacheSize(Cache *c);

    /**
     * Expire any entries from a cache
     * @param c Cache
     */
    extern void cacheExpire(Cache *c);

#ifdef __cplusplus
}
#endif

#endif /* CACHE_H */

