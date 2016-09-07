
#include <stdio.h>
#include <stdlib.h>
#include <area51/json.h>
#include <string.h>

bool json_getBoolean(struct json_object *obj, const char *key) {
    struct json_object *val;
    if (json_object_object_get_ex(obj, key, &val)) {
        return json_object_get_boolean(val);
    }
    return false;
}
