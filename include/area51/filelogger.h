/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   filelogger.h
 * Author: peter
 *
 * Created on 07 September 2016, 19:28
 */

#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <area51/charbuffer.h>
#include <area51/json.h>

#ifdef __cplusplus
extern "C" {
#endif

    // Rotate logs every minute
#define FILELOGGER_ROTATE_MINUTE   1
    // Rotate logs every hour
#define FILELOGGER_ROTATE_HOUR     2
    // Rotate logs ever day
#define FILELOGGER_ROTATE_DAY      3

    typedef struct FileLogger FileLogger;

    /**
     * Create a new FileLogger
     * @param directory (required)
     * @param preifx (optional)
     * @param suffix (optional)
     * @param rotate mode
     * @return FileLogger or NULL
     */
    extern FileLogger *filelogger_new(char *, char *, char *, int);

    /**
     * Create a new FileLogger from JSON config
     * @param json
     * @return FileLogger or NULL
     */
    extern FileLogger *filelogger_new_json(struct json_object *);

    extern void filelogger_log(FileLogger *, char *);
    extern void filelogger_log_r(FileLogger *, char *, int, int);

    extern void filelogger_log_buffer(FileLogger *, CharBuffer *);
    extern void filelogger_log_buffer_r(FileLogger *, CharBuffer *, int, int);

#ifdef __cplusplus
}
#endif

#endif /* FILELOGGER_H */

