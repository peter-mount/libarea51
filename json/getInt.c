
#include <stdio.h>
#include <stdlib.h>
#include <networkrail/json.h>
#include <string.h>

int json_getInt(struct json_object *obj, const char *key) {
    const char *s = (const char *) json_getString(obj, key);
    return s == NULL ? INT_MIN : atoi(s);
}
