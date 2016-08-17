#include <stdlib.h>
#include <string.h>

/*
 * Similar to strcmp but a or b may be null
 */
int comparator_string(char *a, char *b) {
    if (a == b)
        return 0;
    if (a == NULL)
        return -1;
    if (b == NULL)
        return 1;
    return strcmp(a, b);
}
