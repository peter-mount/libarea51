#include <stdlib.h>

int comparator_long(long *a, long *b) {
    return *a == *b ? 0 : *a < *b ? -1 : 1;
}
