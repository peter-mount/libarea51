
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <area51/json.h>

int json_getInt(struct json_object *obj, const char *key) {
    const char *s = (const char *) json_getString(obj, key);
    return s == NULL ? INT_MIN : atoi(s);
}
