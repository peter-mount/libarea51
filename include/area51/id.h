/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   id.h
 * Author: peter
 *
 * Created on 09 September 2016, 20:15
 */

#ifndef AREA51_ID_H
#define AREA51_ID_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct URLIDGenerator URLIDGenerator;

    /**
     * Generate a new generator
     * @param Worker id, 0.. 2^10-1
     * @param seed to randomise the char table
     * @param number of characters to use, min 10 max 64
     * @param max requests per second, max 255. 0 sets max
     * @return URLIDGenerator or NULL on failure
     */
    extern URLIDGenerator *urlidgenerator_new(unsigned int, unsigned int, unsigned int, unsigned int);

    /**
     * Generate a new ID
     * @param URLIDGenerator
     * @param buffer to write into
     * @param max length to write
     */
    extern void urlidgenerator_generate(URLIDGenerator *, char *,int);

#ifdef __cplusplus
}
#endif

#endif /* ID_H */

