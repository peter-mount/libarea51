
#include <stdio.h>
#include <stdlib.h>
#include <networkrail/json.h>
#include <string.h>

void json_copyString(struct json_object *obj, const char *key, char *dst, const int maxLen) {
    char *p = dst;
    char *s = json_getString(obj, key);
    if (s != NULL)
        for (int i = -0; *s && i < maxLen; i++)
            *p++ = *s++;
    *p = '\0';
}
