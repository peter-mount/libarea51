/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Hash map.
 */

#ifndef AREA51___HASHMAP_H
#define AREA51___HASHMAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <area51/list.h>
#include <area51/stream.h>

/** A hash map. */
typedef struct Hashmap Hashmap;

// KeyValue pair - used with Streams

typedef struct KeyValue {
    void *key;
    void *value;
} KeyValue;

/**
 * Creates a new hash map. Returns NULL if memory allocation fails.
 *
 * @param initialCapacity number of expected entries
 * @param hash function which hashes keys
 * @param equals function which compares keys for equality
 */
extern Hashmap* hashmapCreate(size_t initialCapacity,
        int (*hash)(void* key), bool (*equals)(void* keyA, void* keyB));

/**
 * Frees the hash map. Does not free the keys or values themselves.
 */
extern void hashmapFree(Hashmap* map);

/**
 * Hashes the memory pointed to by key with the given size. Useful for
 * implementing hash functions.
 */
extern int hashmapHash(void* key, size_t keySize);

/**
 * Puts value for the given key in the map. Returns pre-existing value if
 * any.
 *
 * If memory allocation fails, this function returns NULL, the map's size
 * does not increase, and errno is set to ENOMEM.
 */
extern void* hashmapPut(Hashmap* map, void* key, void* value);

/**
 * Gets a value from the map. Returns NULL if no entry for the given key is
 * found or if the value itself is NULL.
 */
extern void* hashmapGet(Hashmap* map, void* key);

/**
 * Returns true if the map contains an entry for the given key.
 */
extern bool hashmapContainsKey(Hashmap* map, void* key);

/**
 * Gets the value for a key. If a value is not found, this function gets a 
 * value and creates an entry using the given callback.
 *
 * If memory allocation fails, the callback is not called, this function
 * returns NULL, and errno is set to ENOMEM.
 */
extern void* hashmapMemoize(Hashmap* map, void* key,
        void* (*initialValue)(void* key, void* context), void* context);

/**
 * Removes an entry from the map. Returns the removed value or NULL if no
 * entry was present.
 */
extern void* hashmapRemove(Hashmap* map, void* key);

/**
 * Gets the number of entries in this map.
 */
extern size_t hashmapSize(Hashmap* map);

/**
 * Invokes the given callback on each entry in the map. Stops iterating if
 * the callback returns false.
 */
extern void hashmapForEach(Hashmap* map,
        bool (*callback)(void* key, void* value, void* context),
        void* context);

/**
 * Concurrency support.
 */

/**
 * Locks the hash map so only the current thread can access it.
 */
extern void hashmapLock(Hashmap* map);

/**
 * Unlocks the hash map so other threads can access it.
 */
extern void hashmapUnlock(Hashmap* map);

/**
 * Key utilities.
 */

/**
 * Gets current capacity.
 */
extern size_t hashmapCurrentCapacity(Hashmap* map);

/**
 * Counts the number of entry collisions.
 */
extern size_t hashmapCountCollisions(Hashmap* map);

/**
 * Write the contents of a Hashmap to a file
 */
extern void hashmapWrite(Hashmap *m, bool(*w)(void *k, void *v, void *c), FILE *f);

/**
 * Read a hashmap from a file
 */
extern void hashmapRead(Hashmap *m, bool(*r)(Hashmap *m, FILE *f), FILE *f);
extern int hashmapReadMemMap(Hashmap *m, void *(*r)(Hashmap *m, void *p), int fsock);

// Equals and hashing functions for integer keys. Keys are pointers to the int
extern int hashmapIntHash(void* key);
extern bool hashmapIntEquals(void* keyA, void* keyB);

// Equals and hashing functions for short keys. Keys are pointers to the short
extern int hashmapShortHash(void* key);
extern bool hashmapShortEquals(void* keyA, void* keyB);

// Equals and hashing functions for string keys
extern bool hashmapStringEquals(void *key_a, void *key_b);
extern int hashmapStringHash(void *str);

// Add an item to a list stored within the hashmap
extern struct List *hashmapAddList(Hashmap *m, void *k, void *v);

// Stream mapping: take current value and map it to the value in a hashmap
extern int hashmapGetMapper(Stream *, Hashmap *);

// Return a Stream that will iterate over all entries within the map
extern Stream *hashmapStream(Hashmap *);

// Map a KeyValue to its value
extern void map_keyValue_value(StreamData *);

// Map a KeyValue to its key
extern void map_keyValue_key(StreamData *);

#endif /* __HASHMAP_H */ 