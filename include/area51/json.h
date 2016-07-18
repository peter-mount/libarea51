
/* 
 * File:   json.h
 * Author: peter
 *
 * Created on 18 July 2016, 21:12
 */

#ifndef JSON_H
#define JSON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <json-c/json.h>
    
    /**
     * Get a string parameter from a json_object
     * @param obj json_object
     * @param key key name
     * @return String or null if string is not present, null, "" or " "
     */
    extern char *json_getString(struct json_object *obj, const char *key);
    /**
     * Copy a string from a json_object
     * @param obj json_object
     * @param key key name
     * @param dst destination string, must exist
     * @param maxLen max length of string (excluding null), i.e. sizeof(dst) >= maxLen+1
     */
    extern void json_copyString(struct json_object *obj, const char *key, char *dst, const int maxLen);
    /**
     * Get an integer value
     * @param obj json_object
     * @param key key name
     * @return value or INT_MIN if not present, null etc
     */
    extern int json_getInt(struct json_object *obj, const char *key);
    
    /**
     * Parse a file
     * 
     * @param fsock file handle
     * @return json_object or NULL if not read
     */
    extern struct json_object *json_parse_file(int fsock);
#ifdef __cplusplus
}
#endif

#endif /* JSON_H */

