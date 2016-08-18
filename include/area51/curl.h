/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   source.h
 * Author: peter
 *
 * Created on 01 June 2016, 14:47
 */

#ifndef RULEENGINE_CURL_H
#define RULEENGINE_CURL_H

#include <curl/curl.h>
#include <area51/charbuffer.h>
#include <area51/pool.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern void curl_pool_init(int maxSize);
    extern void curl_pool_free();
    extern CURL *curl_pool_poll();
    extern void curl_pool_offer(CURL *curl);

    extern int curl_get(char *url, CharBuffer *buf);

#ifdef __cplusplus
}
#endif

#endif /* RULEENGINE_CURL_H */

