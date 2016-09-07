
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <area51/log.h>
#include <stdbool.h>
#include <pthread.h>

static bool init = false;
static pthread_mutex_t mutex;

void logconsole(const char *fmt, ...) {
    if (!init) {
        pthread_mutex_init(&mutex, NULL);
        init = true;
    } else
        pthread_mutex_lock(&mutex);

    time_t now = time(NULL);
    struct tm tm;
    localtime_r(&now, &tm);
    char buf[20];
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", &tm);

    va_list argp;

    va_start(argp, fmt);
    fputs(buf, stdout);
    fputc(32, stdout);
    vfprintf(stdout, fmt, argp);
    fputc(10, stdout);
    va_end(argp);

    pthread_mutex_unlock(&mutex);
}

