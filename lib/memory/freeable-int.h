/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   freeable-int.h
 * Author: peter
 *
 * Created on 14 September 2016, 10:21
 */

#ifndef FREEABLE_INT_H
#define FREEABLE_INT_H

#include <stdlib.h>
#include <area51/memory.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct Freeable {
        void *val;
        void (*free)(void *);
    };

#ifdef __cplusplus
}
#endif

#endif /* FREEABLE_INT_H */

