#include <stdlib.h>
#include <time.h>

int comparator_time_t(time_t *a, time_t *b) {
    return *a == *b ? 0 : *a < *b ? -1 : 1;
}
