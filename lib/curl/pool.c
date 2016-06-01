
#include <stdlib.h>
#include <curl/curl.h>
#include <area51/curl.h>

static struct Pool *pool;

static void *createCurl() {
    return (void *) curl_easy_init();
}

static void freeCurl(void *e) {
    if (e)
        curl_easy_cleanup((CURL *) e);
}

void curl_pool_init(int maxSize) {
    if (!pool)
        pool = pool_new(maxSize, createCurl, freeCurl);
}

CURL *curl_pool_poll() {
    return pool ? (CURL*) pool_poll(pool) : NULL;
}

void curl_pool_offer(CURL *curl) {
    if (pool)
        pool_offer(pool, (void *) curl);
}

void curl_pool_free() {
    if (pool) {
        pool_free(pool);
        pool = NULL;
    }
}