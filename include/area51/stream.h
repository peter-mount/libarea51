#ifndef AREA51_STREAM_H
#define AREA51_STREAM_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Stream Stream;

    typedef struct StreamCollector StreamCollector;

    typedef struct StreamTask StreamTask;

    typedef struct StreamData {
        StreamTask *task;
        void *val;
        void (*free)(void *);
    } StreamData;

    extern Stream *stream_new();
    extern Stream *stream_array(void **array, long size);
    extern Stream *stream_of(void *, void (*)(void *));
    extern Stream *stream_range(long, long);
    extern Stream *stream_range_r(long, long, long);

    extern void *stream_run(Stream *, void *);
    extern void stream_next(StreamData *);
    extern void stream_terminate(StreamData *);
    extern void *stream_free(Stream *);

    extern void *stream_getVal(StreamData *d);
    extern void stream_setVal(StreamData *d, void *v, void *f);

    extern int stream_map(Stream *, void *(*)(void *));

    extern int stream_filter(Stream *, bool (*)(void *, void *), void *, void (*)(void *));
    extern int stream_equal(Stream *, void *, void (*)(void *));
    extern int stream_notEqual(Stream *, void *, void (*)(void *));

#define stream_notNull(s) stream_notEqual(s,NULL,NULL);

    extern int stream_onFirst(Stream *s, void (*)(StreamData *));
    extern int stream_notFirst(Stream *s, void (*)(StreamData *));

    extern int stream_findFirst(Stream *);
    extern int stream_limit(Stream *, long);
    extern int stream_skip(Stream *, long);

    extern int stream_forEach(Stream *, void (*)(StreamData *));

    extern void *stream_context(StreamData *);
    extern void *stream_getTaskContext(StreamData *);
    extern void stream_setTaskContext(StreamData *, void *, void (*)(void *));

    extern int stream_invoke(Stream *, void (*)(StreamData *), void *, void (*)(void *));

    extern int stream_collect(Stream *, void *(*)(void *), void (*)(void *, void *), void *(*)(void *));

    extern void stream_debug(Stream *s);

#ifdef __cplusplus
}
#endif

#endif /* AREA51_STREAM_H */
