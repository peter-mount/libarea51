/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   memory.h
 * Author: peter
 *
 * Created on 26 August 2016, 11:40
 */

#ifndef MEMORY_H
#define MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Freeable Freeable;

    /**
     * Create a new Freeable
     * @param value
     * @param free method or NULL
     * @return Freeable or NULL
     */
    extern Freeable *freeable_new(void *, void (*)(void *));

    /**
     * Clear the value from a freeable
     * @param Freeable may be null
     */
    extern void freeable_clear(Freeable *);

    /**
     * Free a Freeable
     * @param Freeable may be null
     */
    extern void freeable_free(Freeable *);
    /**
     * Get the value from a Freeable
     * @param Freeable may be null
     * @return value or null 
     */
    extern void *freeable_get(Freeable *);
    /**
     * Set a freeable, freeing any existing value. If freeable is NULL then
     * a new one is created
     * @param Freeable, if NULL a new one is created
     * @param new Value
     * @param free for new value
     * @return Freeable
     */
    extern Freeable *freeable_set(Freeable *, void *, void (*)(void *));
#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H */

