/* 
 * File:   charbuffer.h
 * Author: peter
 *
 * Created on February 11, 2014, 4:49 PM
 */

#ifndef AREA51_CHARBUFFER_H
#define AREA51_CHARBUFFER_H

#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>

#define CHARBUFFER_OK           0
#define CHARBUFFER_ERROR        1

typedef struct charbuffer CharBuffer;

extern int charbuffer_add(CharBuffer *, char );
extern int charbuffer_append(CharBuffer *, char *);
extern void charbuffer_appendbuffer(CharBuffer *, CharBuffer *);
extern void charbuffer_free(CharBuffer *);
extern CharBuffer *charbuffer_new();
extern int charbuffer_printf(CharBuffer *, char *, ...);
extern int charbuffer_put(CharBuffer *, char *, int );
extern void charbuffer_read(CharBuffer *, FILE *);
extern int charbuffer_readmem(CharBuffer *, int );
extern void charbuffer_reset(CharBuffer *);
extern int charbuffer_size(CharBuffer *);
extern void *charbuffer_toarray(CharBuffer *, int *);
extern char *charbuffer_tostring(CharBuffer *, int *);
extern void *charbuffer_getBuffer(CharBuffer *, int *);

extern void charbuffer_append_int(CharBuffer *, int v, int width);
extern void charbuffer_time_hm(CharBuffer *, double t);
extern void charbuffer_time_hms(CharBuffer *, double t);
extern int charbuffer_append_padleft(CharBuffer *, char *src, int width);
extern int charbuffer_append_padright(CharBuffer *, char *src, int width);
extern int charbuffer_append_center(CharBuffer *, char *src, int width);

// JSON
extern void charbuffer_reset_json(CharBuffer *);
extern void charbuffer_append_json(CharBuffer *, char *n, char *fmt, ...);
extern void charbuffer_end_json(CharBuffer *);

// XML
extern void charbuffer_reset_xml(CharBuffer *, char *tag);
extern void charbuffer_append_xml(CharBuffer *, char *n, char *fmt, ...);
extern void charbuffer_end_xml(CharBuffer *, char *tag);

// Curl
extern int charbuffer_append_urlencode(CharBuffer *, char *src);
extern int charbuffer_append_form_field(CharBuffer *, char *name, char *value);
extern int charbuffer_append_form_fieldf(CharBuffer *, char *name, char *fmt, ...);
extern size_t charbuffer_curl_write(void *b, size_t s, size_t n, void *stream);
extern size_t charbuffer_curl_write_sink(void *b, size_t s, size_t n, void *stream);

extern void charbuffer_replace(CharBuffer *,char *,char *);
extern void charbuffer_replace_int(CharBuffer *,char *,int);

#endif /* CHARBUFFER_H */

