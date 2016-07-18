
#include <stdio.h>
#include <stdlib.h>
#include <area51/json.h>
#include <string.h>

char *json_getString(struct json_object *obj, const char *key) {
    struct json_object *val;
    if (json_object_object_get_ex(obj, key, &val)) {
        const char *s = json_object_get_string(val);
        // Null, empty or " " then return null
        if (s == NULL || *s == 0 || (s[0] == ' ' && s[1] == 0))
            return NULL;
        return (char *) s;
    }
    return NULL;
}
