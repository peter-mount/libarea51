
/* 
 * File:   log.h
 * Author: peter
 *
 * Created on 18 July 2016, 08:13
 */

#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * Write a line to the console.
     * 
     * This will prefix the line with the date and time. It's usually used when a
     * program is used as part of a batch job.
     */
    extern void logconsole(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* LOG_H */

