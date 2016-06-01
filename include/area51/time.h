/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   time.h
 * Author: peter
 *
 * Created on 01 June 2016, 19:19
 */

#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#define _GNU_SOURCE
#include <time.h>

    extern void time_parse_iso8601(struct tm *tm, const char *s);

#ifdef __cplusplus
}
#endif

#endif /* TIME_H */

