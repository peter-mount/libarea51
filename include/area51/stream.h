#ifndef AREA51_STREAM_H
#define AREA51_STREAM_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    // Convert long to void* in arguments
#define stream_long_void(v) ((void *)(v))

    // Convert int to void* in arguments
#define stream_int_void(v) ((void *)((long)(v)))

    // Convert void* to long
#define stream_void_long(v) ((long)(v))

    // Convert void* to int
#define stream_void_int(v) ((int)((long)(v)))

    typedef struct Stream Stream;

    typedef struct StreamCollector StreamCollector;

    typedef struct StreamTask StreamTask;

    typedef struct StreamData StreamData;

    extern Stream *stream_new();
    extern Stream *stream_array(void **array, long size);

    extern Stream *stream_of(void *, void (*)(void *));
#define stream_of_long(v) (stream_of((void *)(v),NULL))
#define stream_of_int(v) (stream_of((void *)((long)(v)),NULL))

    extern Stream *stream_range(long, long);
    extern Stream *stream_range_r(long, long, long);

    extern void *stream_run(Stream *, void *);
    extern void stream_next(StreamData *);
    extern void stream_terminate(StreamData *);
    extern void *stream_free(Stream *);

    extern void *stream_getVal(StreamData *d);
    extern void stream_setVal(StreamData *d, void *v, void *f);

    extern int stream_map(Stream *, void (*)(StreamData *));
    extern int stream_flatMap(Stream *, Stream *(*)(StreamData *, void *), void *);

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

#define stream_invoke(s,a,c,f) stream_invoke_r((s),(a),(c),(f),__PRETTY_FUNCTION__)
    extern int stream_invoke_r(Stream *, void (*)(StreamData *), void *, void (*)(void *), const char *);

    extern int stream_collect(Stream *, void (*)(void *), void (*)(void *, void *), void *(*)(void *), void*, void*);

    extern void stream_debug(Stream *s);

#ifdef __cplusplus
}
#endif

#endif /* AREA51_STREAM_H */
