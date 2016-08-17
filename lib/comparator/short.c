#include <stdlib.h>

int comparator_short(short *a, short *b) {
    return *a == *b ? 0 : *a < *b ? -1 : 1;
}
