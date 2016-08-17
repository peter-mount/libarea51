#include <stdlib.h>

int comparator_double(double *a, double *b) {
    return *a == *b ? 0 : *a < *b ? -1 : 1;
}
