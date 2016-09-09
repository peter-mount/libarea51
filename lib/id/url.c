#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <area51/id.h>
#include <pthread.h>

/*
 * Increment version if algorithm or base is changed
 */
static int version = 0;

#define LENGTH 64
static char *table = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-";

struct URLIDGenerator {
    char table[LENGTH];
    unsigned int workerId : 10;
    // Number of entries in table to use, max LENGTH
    unsigned int length : 6;
    // ID's per second
    unsigned int counter : 8;
    // max value of counter
    unsigned int maxCounter : 8;
    // Time at begining of the month
    time_t base;
    // Time last id was generated
    time_t lastTime;
    // Thread locking
    pthread_mutex_t mutex;
};

/**
 * Generate a new generator
 * @param workerId Worker id
 * @param seed
 * @param length
 * @param maxPerSecond 0 for max allowed
 * @return 
 */
URLIDGenerator *urlidgenerator_new(unsigned int workerId, unsigned int seed, unsigned int length, unsigned int maxPerSecond) {
    if (workerId < 0 || workerId >= (1 << 10))
        return NULL;

    if (length < 10 || length >= LENGTH)
        return NULL;

    if (maxPerSecond < 0 || maxPerSecond > 255)
        return NULL;

    URLIDGenerator *g = malloc(sizeof (URLIDGenerator));
    if (!g)
        return NULL;

    memset(g, 0, sizeof (URLIDGenerator));
    g->workerId = workerId;
    g->length = length;
    g->maxCounter = maxPerSecond ? maxPerSecond : 255;

    time(&g->lastTime);
    strncpy(g->table, table, length);

    pthread_mutex_init(&g->mutex, NULL);

    if (seed) {
        for (int i = 0; i < length; i++) {
            int o = rand_r(&seed) % length;
            char t = g->table[i];
            g->table[i] = g->table[o];
            g->table[o] = t;
        }
    }

    return g;
}

static int encode(URLIDGenerator *g, char *s, int p, int l, long val, bool first) {
    if (!first && !val)
        return p;

    if (p >= l)
        return p;

    int idx;
    if (g->length == LENGTH) {
        idx = (int) (val & 0x3f);
        val >>= 6;
    } else {
        idx = (int) (val % g->length);
        val /= g->length;
    }

    p = encode(g, s, p, l, val, false);
    
    if (p < l)
        s[p++] = g->table[idx];
    
    return p;
}

void urlidgenerator_generate(URLIDGenerator *g, char *s, int l) {
    time_t now, base;
    struct tm tm;

    do {
        time(&now);
        if (now == g->lastTime) {
            g->counter++;
            if (g->counter > g->maxCounter) {
                // Too many so pause until we get a new id
                struct timespec ts;
                ts.tv_nsec = 100000000;
                ts.tv_sec = 0;
                nanosleep(&ts, NULL);
            }
        } else {
            g->counter = 0;
            g->lastTime = now;
        }
    } while (g->counter >= g->maxCounter);

    int p = 0;

    if (version)
        p = encode(g, s, p, l, version, true);

    if (g->workerId)
        p = encode(g, s, p, l, g->workerId, true);

    // Work out a suitable base time for the start of the month
    gmtime_r(&now, &tm);
    tm.tm_mday = tm.tm_hour = tm.tm_min = tm.tm_sec = 0;
    base = mktime(&tm);

    p = encode(g, s, p, l, (long) (((tm.tm_year - 100)*12) + tm.tm_mon), true);

    p = encode(g, s, p, l, (long) (now - base), true);

    if (g->counter)
        p = encode(g, s, p, l, g->counter, true);

    s[p] = 0;
}
