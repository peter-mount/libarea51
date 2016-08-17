#include <stdlib.h>

int comparator_int(int *a, int *b) {
    return *a == *b ? 0 : *a < *b ? -1 : 1;
}
